#ifndef CPP_EXPERIMENTS_MESSAGE_QUEUE_HPP
#define CPP_EXPERIMENTS_MESSAGE_QUEUE_HPP

#include <condition_variable>
#include <map>
#include <mutex>
#include <optional>
#include <queue>

#include "process_id.hpp"

template<typename T>
struct Message {
    T payload;
    ProcessId from;
    ProcessId to;
};

template<typename T>
class MessageQueue {
public:
    auto send(T payload, ProcessId from, ProcessId to) -> void {
        {
            auto lock = std::unique_lock(_mutex);
            _queues[to].emplace(Message<T>{payload, from, to});
        }
        _cv.notify_one();
    }

    auto try_receive(ProcessId id) -> std::optional<Message<T>> {
        auto lock = std::scoped_lock(_mutex);

        if (_queues[id].empty()) { return std::nullopt; }

        if (auto msg = _queues[id].front(); msg.to == id) {
            _queues[id].pop();
            return msg;
        }

        return std::nullopt;
    }

    auto receive(ProcessId id) -> Message<T> {
        auto lock = std::unique_lock(_mutex);
        _cv.wait(lock,
                 [this, id] { return not _queues[id].empty() and _queues[id].front().to == id; });

        const auto msg = std::move(_queues[id].front());
        _queues[id].pop();

        return msg;
    }

private:
    std::map<ProcessId, std::queue<Message<T>>> _queues;
    std::mutex _mutex;
    std::condition_variable _cv;
};

#endif//CPP_EXPERIMENTS_MESSAGE_QUEUE_HPP
