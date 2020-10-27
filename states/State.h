#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED
#include "utility/NonCopyable.h"

class MainGame;
class InputManager;

class State : public NonCopyable
{
public:
	// Constructors/Destructors
	State(MainGame& game);
	virtual ~State();

	//Set 
	inline void needPop(bool status) { m_needPop = status; };
	//Get
	inline const bool& checkForQuit() const { return (m_needPop); };

	//Virtual functions
	virtual void endState() = 0;
	virtual void handleInput(const InputManager& input) = 0;
	virtual void update(const float& deltaTime) = 0;
	virtual void render(SDL_Renderer& render) = 0;

protected:
	MainGame* m_pGame{ nullptr };

private:
	bool m_needPop{ false };
};

#endif	/* end STATE_H_INCLUDED */