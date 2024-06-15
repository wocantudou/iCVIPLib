#ifndef __ICV_Singleton_H__
#define __ICV_Singleton_H__

#include <memory>
#include <mutex>

#define ICVSingletonClass ICV_SAFE_OPENCV::Singleton

namespace ICV_SAFE_OPENCV {

template <typename T> class Singleton {
  public:
    static std::shared_ptr<T> &get_inst() {
        static std::mutex mutex;
        if (inst_ptr_.get() == NULL) {
            std::lock_guard<std::mutex> lock(mutex);
            if (inst_ptr_.get() == NULL) {
                inst_ptr_.reset(new T());
            }
            // 'lock' will be destructed now. 'mutex' will be unlocked.
        }
        return inst_ptr_;
    }

  protected:
    Singleton() {}
    virtual ~Singleton() {}

    // Use shared_ptr to make sure that the allocated memory for instance
    // will be released when program exits (after main() ends).
    static std::shared_ptr<T> inst_ptr_;

  private:
    Singleton(const Singleton &);
    Singleton &operator=(const Singleton &);
};

template <typename T> std::shared_ptr<T> Singleton<T>::inst_ptr_;

} // namespace ICV_SAFE_OPENCV
#endif