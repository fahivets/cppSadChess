#ifndef MAINGAME_H_INCLUDED
#define MAINGAME_H_INCLUDED

#include "utility/NonCopyable.h"
#include "utility/NonMovable.h"
#include "utility/Timer.h"

#include "managers/DisplayManager.h"
#include "managers/InputManager.h"
#include "managers/ResourceHolder.h"

#include "states/StartState.h"

constexpr float constFTimeStep{ 1.0f };
constexpr float constFTimeSlice{ 1.0f };

class MainGame : public NonCopyable, public NonMovable
{
public:
	//Constructors/Destructors
	MainGame();
	~MainGame();

	//Accessors
	bool isRunning() const;

	//Functions
	void update(const float& deltaTime);
	void handleInput();
	void render();
	void run();
	void updateState();

	//DisplayManager geters
	inline SDL_Window& getWindow() const { return (m_display.getWindow()); };
	inline const int& getWinWidth() const { return (m_display.getWinWidth()); };
	inline const int& getWinHeigth() const { return (m_display.getWinHeigth()); };
	inline SDL_Renderer& getRenderer() const { return (m_display.getRenderer()); };
	inline const Vector2f& getWinSize() const { return (m_display.getWinSize()); };

	//States functions
	template<typename T, typename... Args>
	void pushState(Args&&... args);
	void pushState(std::unique_ptr<State> state);

private:
	State& getCurrentState();
	bool initResource();

private:
	bool m_isRunning{ false };
	Timer m_timer;
	DisplayManager m_display;
	InputManager m_input;
	SDL_Event m_event;
	std::stack<std::unique_ptr<State>> m_states;
};

//Template functions
template<typename T, typename... Args>
inline void MainGame::pushState(Args&&... args)
{
	pushState(std::make_unique<T>(std::forward<Args>(args)...));
}

#endif /* end MAINGAME_H_INCLUDED */