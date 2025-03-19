#pragma once
#include <queue>
#include <bitset>


class Keyboard
{

	//Initializing the moutherfucking freind class 
	friend class Window;

public:
	class Event
	{
	public:
		//suck on my nuts
		enum class Type
		{
				Press,
				Release, // You want to fight inteliscence!
				Invalid
		};
		
		//Fight me visual studio i will beat you in a 1v1 in minecraft
	
	
	private:
		Type type;
		unsigned char code;
	
	
	public:
		Event() noexcept
			:
			type(Type::Invalid),
			code(0u)
		{} //Pubes are disgusting

		Event(Type type, unsigned char code) noexcept
			:
			type(type),
			code(code)
		{}

		bool IsPress() const noexcept // my cock is actually 9 inch long 
		{
			return type == Type::Press;
		}
		bool IsRelease() const noexcept // 8=============D 
		{
			return type != Type::Invalid;	
		}
		unsigned char GetCode() const noexcept
		{
			return code;
		}
	};

public:
	
	//send boob pics
	
	
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;

	//Key event 
	bool KeyIsPressed(unsigned char keycode) const noexcept;
	Event ReadKey() noexcept;
	bool KeyIsEmpty() const noexcept;
	void FlushKey() noexcept;

	// char event stuff
	char ReadChar() noexcept;
	bool CharIsEmpty() const noexcept;
	void FlushChar() noexcept;
	void Flush() noexcept;

	//autorepeat control 
	
	void EnableAutorepeat() noexcept;
	void DisableAutorepeat() noexcept;
	bool AutorepeatIsEnabled() const noexcept;

private:
	void OnKeyPressed(unsigned char keycode) noexcept;
	void OnKeyReleased(unsigned char keycode) noexcept;
	void OnChar(char character) noexcept;
	void ClearState() noexcept;

	template<typename T>
	static void TrimBuffer(std::queue<T>& buffer) noexcept;

	//8==================================================================D
private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keystates;
	std::queue<Event> keybuffer;
	std::queue<char> charbuffer;





};




