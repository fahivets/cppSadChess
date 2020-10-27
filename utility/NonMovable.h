#ifndef NONMOVABLE_H_INCLUDED
#define NONMOVABLE_H_INCLUDED

class NonMovable
{
public:
	NonMovable(NonMovable&&) = delete;
	NonMovable& operator=(NonMovable&&) = delete;

protected:
	NonMovable() = default;
	~NonMovable() = default;
};

#endif /* end NONMOVABLE_H_INCLUDED */