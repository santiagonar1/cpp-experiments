#ifndef CPP_EXPERIMENTS_EVENT_HPP
#define CPP_EXPERIMENTS_EVENT_HPP

template<typename T>
struct Event {
    T type;
    unsigned int process_id;
    unsigned int timestamp;
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const Event<T> &e) {
    return os << "Event{type=" << e.type << ", process_id=" << e.process_id
              << ", timestamp=" << e.timestamp << "}";
}

#endif//CPP_EXPERIMENTS_EVENT_HPP
