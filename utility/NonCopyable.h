#ifndef NONCOPYABLE_H_INCLUDED
#define NONCOPYABLE_H_INCLUDED

class NonCopyable
{
public:
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;

	NonCopyable(NonCopyable&&) = default;
	NonCopyable& operator=(NonCopyable&&) = default;

protected:
	NonCopyable() = default;
	~NonCopyable() = default;
};

#endif /* end NONCOPYABLE_H_INCLUDED */