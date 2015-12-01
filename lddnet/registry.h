// registry.h (2013-05-29)
// Li Xinjie (xjason.li@gmail.com)

#ifndef LDD_NET_REGISTRY_H_
#define LDD_NET_REGISTRY_H_

#include <map>
#include "ldd/net/factory.h"

namespace ldd {
namespace net {

/*
 * T 指的是IncomingMsg或OutgoingMsg基类
 * Tag 指的是MsgType类型,MsgType目前是一个int16_t的整数
 * 这里的int是默认值，可以动态指定为int16_t
 *
 * */

template <class T, class Tag = int>
class Registry {
public:
    virtual ~Registry();

    /*D指的是IncomingMsg或OutgoingMsg派生类*/
    template <class D>
    void Register(Tag n) {
        RegisterFactory(n, Factory<T>::template NewFactory<D>());
    }
    template <class D, class A1>
    void Register(Tag n, A1 a1) {
        RegisterFactory(n, Factory<T>::template NewFactory<D>(a1));
    }
    template <class D, class A1, class A2>
    void Register(Tag n, A1 a1, A2 a2) {
        RegisterFactory(n, Factory<T>::template NewFactory<D>(a1, a2));
    }
    template <class D, class A1, class A2, class A3>
    void Register(Tag n, A1 a1, A2 a2, A3 a3) {
        RegisterFactory(n, Factory<T>::template NewFactory<D>(a1, a2, a3));
    }
    template <class D, class A1, class A2, class A3, class A4>
    void Register(Tag n, A1 a1, A2 a2, A3 a3, A4 a4) {
        RegisterFactory(n, Factory<T>::template NewFactory<D>(a1, a2, a3, a4));
    }
    template <class D, class A1, class A2, class A3, class A4, class A5>
    void Register(Tag n, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
        RegisterFactory(n, Factory<T>::template NewFactory<D>(a1, a2, a3, a4, a5));
    }
    template <class D, class A1, class A2, class A3, class A4, class A5, class A6>
    void Register(Tag n, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
        RegisterFactory(n, Factory<T>::template NewFactory<D>(a1, a2, a3, a4, a5, a6));
    }
    template <class D, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    void Register(Tag n, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) {
        RegisterFactory(n, Factory<T>::template NewFactory<D>(a1, a2, a3, a4, a5, a6, a7));
    }
    template <class D, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    void Register(Tag n, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) {
        RegisterFactory(n, Factory<T>::template NewFactory<D>(a1, a2, a3, a4, a5, a6, a7, a8));
    }
    template <class D, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    void Register(Tag n, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) {
        RegisterFactory(n, Factory<T>::template NewFactory<D>(a1, a2, a3, a4, a5, a6, a7, a8, a9));
    }
    template <class D, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    void Register(Tag n, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) {
        RegisterFactory(n, Factory<T>::template NewFactory<D>(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10));
    }

    T* New(Tag n) const;
    boost::shared_ptr<T> MakeShared(Tag n) const;
private:
    void RegisterFactory(Tag n, Factory<T>* f);
    std::map<Tag, Factory<T>*> factories_;
};

template <class T, class Tag>
inline void Registry<T, Tag>::RegisterFactory(Tag n, Factory<T>* f) {
    typedef typename std::map<Tag, Factory<T>*>::iterator iterator;
    std::pair<iterator, bool> result = factories_.insert(std::make_pair(n, f));
    if (!result.second) {
        delete result.first->second;
        result.first->second = f;
    }
}

template <class T, class Tag>
inline T* Registry<T, Tag>::New(Tag n) const {
    typedef typename std::map<Tag, Factory<T>*>::const_iterator iterator;
    iterator iter = factories_.find(n);
    if (iter == factories_.end()) {
        return NULL;
    }
    return iter->second->New();
}

template <class T, class Tag>
inline boost::shared_ptr<T> Registry<T, Tag>::MakeShared(Tag n) const {
    typedef typename std::map<Tag, Factory<T>*>::const_iterator iterator;
    iterator iter = factories_.find(n);
    if (iter == factories_.end()) {
        return boost::shared_ptr<T>();
    }
    return iter->second->MakeShared();
}

template <class T, class Tag>
inline Registry<T, Tag>::~Registry() {
    typedef typename std::map<Tag, Factory<T>*>::iterator iterator;
    for (iterator iter = factories_.begin(); iter != factories_.end(); ++iter) {
        delete iter->second;
    }
    factories_.clear();
}

} // namespace net
} // namespace ldd

#endif // LDD_NET_REGISTRY_H_
