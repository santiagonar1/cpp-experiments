#include <algorithm>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include <event.hpp>
#include <message_queue.hpp>
#include <process_id.hpp>
#include <random_generator.hpp>

enum class EventType {
    START,
    PROCESS,
    SEND_MSG,
    RECEIVE_MSG,
    FINISHED,
};

std::ostream &operator<<(std::ostream &os, EventType e) {
    switch (e) {
        case EventType::START:
            return os << "START";
        case EventType::PROCESS:
            return os << "PROCESS";
        case EventType::SEND_MSG:
            return os << "SEND_MSG";
        case EventType::RECEIVE_MSG:
            return os << "RECEIVE_MSG";
        case EventType::FINISHED:
            return os << "FINISHED";
    }
    return os << "DummyEvent{<unknown>}";
}

std::mutex mutex;
auto msg_queue = MessageQueue<Event<EventType>>{};
void emulate_process(const ProcessId id, const unsigned int num_events,
                     const unsigned int num_processes) {
    auto events = std::vector{Event{EventType::START, id, 0}};
    auto finished = std::vector(num_processes, false);

    for (unsigned int i = 0; i < num_events; ++i) {
        const auto tick_length = get_random_int(1, 7);
        const auto tick = events.back().timestamp + tick_length;
        events.emplace_back(EventType::PROCESS, id, tick);

        if (id == 0) {
            const auto event =
                    Event(EventType::SEND_MSG, id, events.back().timestamp + tick_length);
            msg_queue.send(event, id, num_processes - 1);
            events.push_back(event);
        }

        if (const auto msg = msg_queue.try_receive(id); msg.has_value()) {
            const auto received_event = msg.value().payload;
            const auto timestamp_received = received_event.timestamp;
            const auto current_timestamp = events.back().timestamp;
            const auto greater_timestamp = std::max(timestamp_received, current_timestamp);

            if (received_event.type == EventType::FINISHED) {
                finished[msg.value().from] = true;
                events.push_back(Event(EventType::FINISHED, id, greater_timestamp + tick_length));
                continue;
            }

            events.push_back(Event(EventType::RECEIVE_MSG, id, greater_timestamp + tick_length));
        }
    }

    // Signal to all that I finished
    for (unsigned int i = 0; i < num_processes; ++i) {
        const auto finished_event = Event(EventType::FINISHED, id, events.back().timestamp + 1);
        events.push_back(finished_event);
        msg_queue.send(finished_event, id, i);
    }

    // Wait to all to finish
    while (not std::ranges::all_of(finished, [](const bool f) { return f; })) {
        if (const auto msg = msg_queue.try_receive(id); msg.has_value()) {
            const auto received_event = msg.value().payload;
            const auto timestamp_received = received_event.timestamp;
            const auto current_timestamp = events.back().timestamp;
            const auto greater_timestamp = std::max(timestamp_received, current_timestamp);

            if (received_event.type == EventType::FINISHED) {
                finished[msg.value().from] = true;
                events.push_back(Event(EventType::FINISHED, id, greater_timestamp + 1));
                continue;
            }

            events.push_back(Event(EventType::RECEIVE_MSG, id, greater_timestamp + 1));
        }
    }


    auto lock = std::lock_guard{mutex};
    std::cout << "Process " << id << " emulating " << num_events << " events:" << std::endl;
    for (const auto &event: events) { std::cout << event << std::endl; }
    std::cout << std::endl;
}

int main() {
    auto threads = std::vector<std::jthread>{};
    constexpr auto num_processes = 5;
    threads.emplace_back(emulate_process, 0, 10, num_processes);

    for (unsigned int i = 1; i < num_processes; ++i) {
        threads.emplace_back(emulate_process, i, 3, num_processes);
    }

    return 0;
}