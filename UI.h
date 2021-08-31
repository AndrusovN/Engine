#ifndef UI
#define UI

#include <iostream>

#include <SFML/Graphics.hpp>
#include <windows.h>
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include "Engine.h"
using namespace std;
using namespace sf;

class Button : public Component {
public:

	void set(Vector2f Position) {
		_position = Position;
		_B.setPosition(_position);
	}
	void set(Vector2i Window) {
		_WinPos = (Vector2f)Window;

	}
	void CK() {
		bool a = CheckPress();
	}
	void set(Vector2f Scale, int i) {
		_B.setScale(Scale);
	}
	void set(Vector2f Position, Vector2f Scale, Color c, Texture t, Sprite But, Vector2f Window, wstring bs) {
		_myFont.loadFromFile("Data\\Sh.otf");
		_position = Position;
		_scale = Scale;
		_color = c;
		_texture = t;
		_B = But;
		_B.setTexture(_texture);
		_B.setPosition(_position);
		_B.setScale(_scale);
		_WinPos = Window;
		_BS = bs;
		_BT.setFillColor(Color(0, 0, 0));
		_BT.setFont(_myFont);
		_BT.setCharacterSize(120 * (Scale.x + Scale.y) / 2);
		_BT.setPosition(_position);
		_BT.setString(_BS);
		_BT.setFillColor(Color(255, 255, 255));
		_texturePRESSED = _texture;
		_typeB = 1;
	}
	void set(Vector2f Position, Vector2f Scale, Color c, Texture t, Texture tP, Font myFont, Sprite But, Vector2f Window, wstring bs, int ChS) {
		_myFont = myFont;//.loadFromFile("Data\\Sh.otf");
		_position = Position;
		_scale = Scale;
		_color = c;
		_texture = t;
		_B = But;
		_B.setTexture(_texture);
		_B.setPosition(_position);
		_B.setScale(_scale);
		_WinPos = Window;
		_BS = bs;
		_BT.setFillColor(Color(255, 255, 255));
		_BT.setFont(_myFont);
		_BT.setCharacterSize(ChS);
		float q = 0.39;
		float p = 1.3;
		_BT.setPosition(_position + Vector2f((t.getSize().x*Scale.x - bs.length()*ChS* q) / 2, ((t.getSize().y*Scale.y) - ChS * p) / 2));
		_BT.setString(_BS);
		_texturePRESSED = tP;
		_typeB = 0;
	}



	bool CheckPress(int a) {
		return(_IsPressed);
	}

	void(*onClick)();
	RenderWindow * window;


	void Awake(){}
	void Start(){}
	void LateUpdate(){}
	void Update(){
		CheckPress();
		window->draw(_B);
		window->draw(_BT);
	}

	bool CheckPress() {
		Texture non;
		if (_typeB == 0) {
			if ((Mouse::getPosition().x > _position.x + _WinPos.x) && (Mouse::getPosition().x < _position.x + _WinPos.x + _texture.getSize().x * _scale.x) &&
				(Mouse::getPosition().y > _position.y + _WinPos.y + 30) && (Mouse::getPosition().y < _position.y + _WinPos.y + _texture.getSize().y * _scale.y + 30)) {


				if ((_wasmousepressed == true) && (!Mouse::isButtonPressed(Mouse::Left))) {
					_IsPressed = true;
				}
				else
				{
					_IsPressed = false;
				}
				if (Mouse::isButtonPressed(Mouse::Left)) {
					_wasmousepressed = true;

					_B.setTexture(_texturePRESSED);

				}
				else
				{

					_wasmousepressed = false;
					_B.setTexture(_texture);
				}

			}
			else
			{
				_IsPressed = false;
				_B.setTexture(_texture);
				_wasmousepressed = false;

			}
			if ((!Mouse::isButtonPressed(Mouse::Left))) {
				_wasmousepressed = false;
			}

		}
		else

		{

			if ((Mouse::getPosition().x > _position.x + _WinPos.x) && (Mouse::getPosition().x < _position.x + _WinPos.x + _texture.getSize().x * _scale.x) &&
				(Mouse::getPosition().y > _position.y + _WinPos.y + 30) && (Mouse::getPosition().y < _position.y + _WinPos.y + _texture.getSize().y * _scale.y + 30) &&
				(Mouse::isButtonPressed(Mouse::Left))) {

				_IsPressed = true;
				_B.setTexture(_texturePRESSED);

			}
			else
			{

				_IsPressed = false;

				_B.setTexture(_texture);
			}
		}
		if (_IsPressed) {
			(*onClick)();
		}
		return(_IsPressed);
	}
	Sprite GetButton() {
		return(_B);
	}
	Text getText() {
		return(_BT);
	}


private:
	Font _myFont;
	Text _BT;
	wstring _BS;
	Vector2f _position;
	Vector2f _scale;
	Color _color;
	Texture _texture;
	bool _IsPressed;
	Vector2f _WinPos;
	Sprite _B;
	int _typeB;
	Texture _texturePRESSED;
	bool _wasmousepressed = false;
protected:

};

/*class Scrollbar {
public:


	void set(Texture lT, Texture sT, int Diap, Vector2f lP, Vector2i WindowP, Vector2f lS, Vector2f sS, int n, Sprite LineSprite, int DiapL) {
		_line = LineSprite;
		_lineT = lT;
		_lineS = lS;
		_lineP = (Vector2i)lP;
		_line.setTexture(_lineT);
		_line.setPosition(lP);
		_diapLength = DiapL;
		_line.setScale(lS);
		_scrollerT = sT;
		_scrollerS = sS;
		_scroller.set(Vector2f(_line.getPosition().x + sS.x*sT.getSize().x / 2 + n * (((DiapL)-(sT.getSize().x*sS.x)) / Diap),
			_line.getPosition().y - sS.y*sT.getSize().y / 2 + lT.getSize().y*lS.y / 2), (Vector2f)sS, Color(255, 100, 100), sT, _Sc, (Vector2f)WindowP, L"");

		_windowPos = WindowP;

		_diapazon = Diap;
		_value = n;
	}
	void UpdateData(Vector2i WinPos) {
		_windowPos = WinPos;
		_scroller.set(WinPos);
		if (_wasPressed) {

			if (Mouse::isButtonPressed(Mouse::Left)) {

				_wasPressed = true;
			}
			else
			{
				_wasPressed = false;
			}
		}
		else
		{

			if (_scroller.CheckPress()) {

				_wasPressed = true;

			}
			else
			{

				_wasPressed = false;
			}
		}

		if (_wasPressed) {

			if (Mouse::getPosition().x >= _line.getPosition().x + _scrollerS.x * _scrollerT.getSize().x / 2 +
				_windowPos.x) {

				if (Mouse::getPosition().x <= _line.getPosition().x + _lineT.getSize().x*_lineS.x - _scrollerT.getSize().x*_scrollerS.x / 2 + _windowPos.x) {

					_scroller.set(Vector2f(Mouse::getPosition().x - _windowPos.x - _scrollerT.getSize().x*_scrollerS.x / 2, _scroller.GetButton().getPosition().y),
						_scroller.GetButton().getScale(), Color(), _scrollerT, _scroller.GetButton(), (Vector2f)_windowPos, L"");
					_value = (_scroller.GetButton().getPosition().x - _line.getPosition().x) /
						(_lineT.getSize().x*_lineS.x - _scrollerT.getSize().x*_scrollerS.x) * _diapazon;

				}
				else
				{

					_value = _diapazon;

					_scroller.set(Vector2f(_line.getPosition().x + _lineT.getSize().x*_lineS.x - _scrollerT.getSize().x*_scrollerS.x, _scroller.GetButton().getPosition().y));

				}
			}
			else
			{
				_value = 0;
				_scroller.set(Vector2f(_line.getPosition().x, _scroller.GetButton().getPosition().y));
			}
		}




	}
	int getValue(Vector2i winpos) {
		UpdateData(winpos);
		return(_value);
	}
	Sprite getLine() {
		return(_line);
	}
	Sprite getScroller(Vector2i winpos) {

		return(_scroller.GetButton());
	}
private:
	Sprite _line;
	Button _scroller;
	Sprite _Sc;
	Texture _lineT;
	Texture _scrollerT;
	int _value = 0;
	int _diapazon;
	bool _wasPressed;
	Vector2i _lineP;
	Vector2i _windowPos;
	Vector2f _lineS;
	Vector2f _scrollerS;
	int _diapLength;
};

class TextField {
public:

	void set(Color c, Font f, Vector2f pos, int size, Vector2f scale, Vector2f window) {

		_fieldAreaT.loadFromFile("Data\\TextField1.png");
		_resultT.setFillColor(c);
		_resultT.setCharacterSize(round(70 * scale.y));
		_position = pos;
		_resultT.setPosition(_position + Vector2f(30 * scale.x, (_fieldAreaT.getSize().y*scale.y - 70 * scale.y) / 4));
		_thisColor = c;

		_font = f;
		_resultT.setFont(_font);
		_fieldCursorT.loadFromFile("Data\\Cursor.png");
		_fieldArea.set(pos, scale, Color(), _fieldAreaT, _fieldAreaS, (Vector2f)window, L"");
		_timer = 0;
		_fieldCursor.setTexture(_fieldCursorT);
		_startTimer = 100;
		_fieldCursor.setScale(Vector2f(_fieldArea.GetButton().getScale().x*_num, _fieldArea.GetButton().getScale().y*_num));
		_fieldCursor.setPosition(_position + Vector2f((_cursNum + 1)*_k + 40 * scale.x, 10));
		_k = scale.x * 40;
	}
	Sprite getCursor() {

		return(_fieldCursor);
	}
	Sprite getTextField() {
		return(_fieldArea.GetButton());
	}
	Text getText() {

		return(_resultT);
	}
	string getString() {

		return(_textS);
	}
	void setString(string ToSet) {
		_textS = ToSet;
		_cursNum = ToSet.size() - 1;
	}
	void updateDATA(Vector2i Winpos) {
		UpdateData(Winpos);
	}
	bool WasEntered;
private:
	Text _resultT;
	Color _thisColor;
	string _textS;
	Vector2f _position;
	Font _font;
	Button _fieldArea;
	Texture _fieldAreaT;
	Sprite _fieldAreaS;
	Texture _fieldCursorT;
	Sprite _fieldCursor;
	Window _thisWindow;
	int _timer;
	int _k = 22;
	int _num = 0;
	int _startTimer;
	int _cursNum = -1;
	char _thisPress;

	bool _isBackSpaced;
	bool _waspressed;
	int _move;
	bool _isActive;
	bool _lastWasPress;
	bool _wasPasted;
	bool _oldWasPasted;
	bool _willWasEntered = false;
	void _getPressedString() {

		if (Keyboard::isKeyPressed(Keyboard::Escape)) { _isActive = false; }
		if (Keyboard::isKeyPressed(Keyboard::Return)) { _isActive = false; WasEntered = true; }
		else { WasEntered = false; }
		if (Keyboard::isKeyPressed(Keyboard::LShift)) {
			if (Keyboard::isKeyPressed(Keyboard::Semicolon)) { _thisPress = ':'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num1)) { _thisPress = '!'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num2)) { _thisPress = '@'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num3)) { _thisPress = '#'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num4)) { _thisPress = '$'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num5)) { _thisPress = '%'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num0)) { _thisPress = ')'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num6)) { _thisPress = '^'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num7)) { _thisPress = '&'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num8)) { _thisPress = '*'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num9)) { _thisPress = '('; _waspressed = true; }

			if (Keyboard::isKeyPressed(Keyboard::Q)) { _thisPress = 'Q'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::W)) { _thisPress = 'W'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::E)) { _thisPress = 'E'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::R)) { _thisPress = 'R'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::T)) { _thisPress = 'T'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Y)) { _thisPress = 'Y'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::U)) { _thisPress = 'U'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::I)) { _thisPress = 'I'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::O)) { _thisPress = 'O'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::P)) { _thisPress = 'P'; _waspressed = true; }

			if (Keyboard::isKeyPressed(Keyboard::A)) { _thisPress = 'A'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::S)) { _thisPress = 'S'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::D)) { _thisPress = 'D'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::F)) { _thisPress = 'F'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::G)) { _thisPress = 'G'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::H)) { _thisPress = 'H'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::J)) { _thisPress = 'J'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::K)) { _thisPress = 'K'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::L)) { _thisPress = 'L'; _waspressed = true; }

			if (Keyboard::isKeyPressed(Keyboard::Z)) { _thisPress = 'Z'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::X)) { _thisPress = 'X'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::C)) { _thisPress = 'C'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::LControl)) { _wasPasted = true; _waspressed = true; }
			else {
				if (Keyboard::isKeyPressed(Keyboard::V)) { _thisPress = 'V'; _waspressed = true; }
			}
			if (Keyboard::isKeyPressed(Keyboard::B)) { _thisPress = 'B'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::N)) { _thisPress = 'N'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::M)) { _thisPress = 'M'; _waspressed = true; }

			if (Keyboard::isKeyPressed(Keyboard::Slash)) { _thisPress = '?'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::BackSlash)) { _thisPress = '|'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Period)) { _thisPress = '>'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Comma)) { _thisPress = '<'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Equal)) { _thisPress = '+'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Hyphen)) { _thisPress = '_'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Space)) { _thisPress = ' '; _waspressed = true; }
		}
		else
		{
			if (Keyboard::isKeyPressed(Keyboard::Num1)) { _thisPress = '1'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num2)) { _thisPress = '2'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num3)) { _thisPress = '3'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num4)) { _thisPress = '4'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num5)) { _thisPress = '5'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num0)) { _thisPress = '0'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num6)) { _thisPress = '6'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num7)) { _thisPress = '7'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num8)) { _thisPress = '8'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num9)) { _thisPress = '9'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Q)) { _thisPress = 'q'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::W)) { _thisPress = 'w'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::E)) { _thisPress = 'e'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::R)) { _thisPress = 'r'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::T)) { _thisPress = 't'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Y)) { _thisPress = 'y'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::U)) { _thisPress = 'u'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::I)) { _thisPress = 'i'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::O)) { _thisPress = 'o'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::P)) { _thisPress = 'p'; _waspressed = true; }

			if (Keyboard::isKeyPressed(Keyboard::A)) { _thisPress = 'a'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::S)) { _thisPress = 's'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::D)) { _thisPress = 'd'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::F)) { _thisPress = 'f'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::G)) { _thisPress = 'g'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::H)) { _thisPress = 'h'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::J)) { _thisPress = 'j'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::K)) { _thisPress = 'k'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::L)) { _thisPress = 'l'; _waspressed = true; }

			if (Keyboard::isKeyPressed(Keyboard::Z)) { _thisPress = 'z'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::X)) { _thisPress = 'x'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::C)) { _thisPress = 'c'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::LControl)) { _wasPasted = true; _waspressed = true; }
			else {
				if (Keyboard::isKeyPressed(Keyboard::V)) { _thisPress = 'v'; _waspressed = true; }
			}
			if (Keyboard::isKeyPressed(Keyboard::B)) { _thisPress = 'b'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::N)) { _thisPress = 'n'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::M)) { _thisPress = 'm'; _waspressed = true; }

			if (Keyboard::isKeyPressed(Keyboard::Slash)) { _thisPress = '/'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::BackSlash)) { _thisPress = '\\'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Period)) { _thisPress = '.'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Comma)) { _thisPress = ','; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Equal)) { _thisPress = '='; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Hyphen)) { _thisPress = '-'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Space)) { _thisPress = ' '; _waspressed = true; }



		}
		if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
			_isBackSpaced = true; _waspressed = true;
		}
		else { _isBackSpaced = false; }
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			_move = -1; _waspressed = true;
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				_move = 1; _waspressed = true;
			}
			else { _move = 0; }
		}
	}
	void UpdateData(Vector2i winpos) {
		_fieldArea.set(winpos);
		if (_willWasEntered) {
			WasEntered = false;
		}
		if (_fieldArea.CheckPress()) {
			if (!_isActive) {
				_isActive = true;
			}
		}
		else
		{
			if (Mouse::isButtonPressed(Mouse::Left)) {
				_isActive = false;

			}
		}
		if (_isActive) {
			_lastWasPress = _waspressed;
			_waspressed = false;
			if (_wasPasted) {
				_oldWasPasted = true;
			}
			_getPressedString();
			if (WasEntered) {
				if (!_willWasEntered) {
					_willWasEntered = true;

				}
			}
			else
			{
				_willWasEntered = false;

			}
			if (_oldWasPasted) {
				_wasPasted = false;
			}
			if (!_waspressed) {
				_thisPress = (char)"";
			}

			if (_waspressed && !_lastWasPress && !_wasPasted) {

				if ((_cursNum + _move > -2)) {
					if (((_cursNum + _move + 10) < _textS.size() + 10)) {
						_cursNum += _move;
					}

				}

				if (_isBackSpaced) {
					if (_cursNum > -1) {
						for (int i = _cursNum; i < _textS.length() - 1; i++) {
							_textS[i] = _textS[i + 1];
						}
						_textS.resize(_textS.length() - 1);
						_cursNum--;
					}
				}
				if (_move == 0 && !_isBackSpaced) {
					_textS.resize(_textS.length() + 1);
					for (int a = _textS.length() - 1; a > _cursNum + 1; a--) {
						_textS[a] = _textS[a - 1];
					}
					_textS[_cursNum + 1] = _thisPress;
					_cursNum++;
				}
			}

			if (_timer > 0) {
				_timer--;
			}
			else
			{
				_num = 1 - _num;

				_timer = _startTimer;
				_fieldCursor.setScale(Vector2f(_fieldArea.GetButton().getScale().x*_num / 2, _fieldArea.GetButton().getScale().y*_num));

			}
			_fieldCursor.setPosition(_position + Vector2f((_cursNum + 1)*_k + 40 * _fieldArea.GetButton().getScale().x, 10));

		}
		else {
			_fieldCursor.setScale(Vector2f(0, 0));

		}
		_resultT.setString(_textS);
	}
};
*/
#endif
