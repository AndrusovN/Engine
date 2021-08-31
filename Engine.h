#ifndef ENGINE
#define ENGINE

#include <dos.h>
#include <iostream>
#include "List.h"
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#pragma warning (disable:4996)
//#include "UI.h"
using namespace std;
using namespace sf;

class GameObject;
int W = 1280;
int H = 868;



	bool compareStrings(string a, string b) {
		int l;
		if (a.length() > b.length()) {
			l = b.length();
		}
		else
		{
			l = a.length();
		}


		for (int i = 0; i < l; i++)
		{
			if (a[i] != b[i]) {
				return(false);
			}
		}
		return(true);
	}

	class Component {
	public:
		GameObject* gameObject;
		string componentName = "Unknown component";
		virtual void Start() = 0;
		virtual void Awake() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
	};

	class GameObject {
	public:
		List<Component*> components;
		template<class T>
		T* GetComponent() {
			for (int i = 0; i < components.length(); i++)
			{
				if (typeid(T) == typeid(*components.get(i))) {
					return(dynamic_cast<T*>(components.get(i)));
				}

			}
			return(0);
		}
	};

	/*class EngineTime {
	public:
		double delta;
		double fps;
		void recalculate() {
			frame++;
			
		}
		void showTime() {
			time_t timer;
			time(&timer);
			cout << (int)timer << endl;
		}

	private:
		int oldtime;
		int frame = 0;
	};*/

	class _Transform;

	class Scene {
	public:
		//EngineTime time;
		RenderWindow * window;
		List<GameObject> objects;
		template <class T>
		List<T*> getComponents() {
			List<T*> res = List<T*>();
			for (int i = 0; i < objects.length(); i++)
			{
				for (int j = 0; j < objects.get(i).components.length(); j++)
				{
					//cout << typeid(*objects.get(i).components.get(j)).hash_code() << " " << typeid(T()).hash_code() << endl;
					//cout << typeid(*objects.get(i).components.get(j)).name() << " " << typeid(T()).name() << endl;
					if (compareStrings(typeid(*objects.get(i).components.get(j)).name(), typeid(T()).name())) {
						//cout << "success" << endl;
						res.append(dynamic_cast<T*>(objects.get(i).components.get(j)));
					}

				}
			}
			return(res);
		}
		void PLAY() {
			

			for (int i = 0; i < objects.length(); i++)
			{
				for (int j = 0; j < objects.get(i).components.length(); j++)
				{
					objects.get(i).components.get(j)->Awake();
				}
			}

			for (int i = 0; i < objects.length(); i++)
			{
				for (int j = 0; j < objects.get(i).components.length(); j++)
				{
					objects.get(i).components.get(j)->Start();
				}
			}

			while (window->isOpen()) {
				//EngineTime t;
				//t.showTime();
				Event event;
				while (window->pollEvent(event)) {
					if (event.type == Event::Closed) {


						window->close();
					}
				}
				window->clear();

				for (int i = 0; i < objects.length(); i++)
				{
					for (int j = 0; j < objects.get(i).components.length(); j++)
					{
						objects.get(i).components.get(j)->Update();
					}
				}

				for (int i = 0; i < objects.length(); i++)
				{
					for (int j = 0; j < objects.get(i).components.length(); j++)
					{
						objects.get(i).components.get(j)->LateUpdate();
					}
				}
				window->display();
			}
		}
	};

	class _Vector3 {
	public:
		double x;
		double y;
		double z;
		_Vector3() {
			x = 0;
			y = 0;
			z = 0;
		}
		_Vector3(double _x, double _y, double _z) {
			this->x = _x;
			this->y = _y;
			this->z = _z;
		}
		_Vector3 operator * (double a) {
			return(_Vector3(this->x *a, this->y *a, this->z *a));
		}

		_Vector3 operator + (_Vector3 a) {
			return(_Vector3(this->x + a.x, this->y + a.y, this->z + a.z));
		}

		_Vector3 operator - (_Vector3 a) {
			return(*this + a * -1);
		}

		bool operator == (_Vector3 a) {
			return((a.x == this->x) && (a.y == this->y) && (a.z == this->z));
		}

		bool operator != (_Vector3 a) {
			return(!(a == *this));
		}

		_Vector3 operator / (double a) {
			return(*this * (1 / a));
		}

		double length() {
			double res = sqrt(x * x + y * y + z * z);
			return(res);
		}
		_Vector3 normalize() {
			return(*this / this->length());
		}

		_Vector3 operator * (_Vector3 a) {
			double x = a.y * this->z - a.z * this->y;
			double y = a.z * this->x - a.x * this->z;
			double z = a.x * this->y - a.y * this->x;
			return (_Vector3(x, y, z));
		}

		double operator >> (_Vector3 a) {
			_Vector3 _a = a;// .normalize();
			_Vector3 _b = *this;// ->normalize();
			double res = _a.x * _b.x + _a.y * _b.y + _a.z * _b.z;
			return (res);
		}

		_Vector3 operator << (_Vector3 a) {
			_Vector3 res = _Vector3(a.x * this->x, a.y * this->y, a.z * this->z);
			return res;
		}

		double distance(_Vector3 direction) {
			return((*this - direction).length());
		}

		double angle(_Vector3 second) {
			return(
				acos(this->normalize() >> second.normalize()));

		}



	};

	class _Transform : public Component {
	public:
		_Vector3 position;
		_Vector3 rotation;
		_Vector3 scale;

		_Vector3 forward;
		_Vector3 right;
		_Vector3 up;

		_Transform() {
			position = _Vector3(0, 0, 0);
			rotation = _Vector3(0, 0, 0);
			scale = _Vector3(1, 1, 1);
			forward = _Vector3(0, 0, 1);
			right = _Vector3(1, 0, 0);
			up = _Vector3(0, 1, 0);
		}

		void Awake() {
			componentName = "_Transform";
		}
		void Start() {}
		void Update() {
			/*forward.x = sin(rotation.y) * cos(rotation.x);
			forward.y = sin(rotation.x) * cos(rotation.y);
			forward.z = cos(rotation.y) * cos(rotation.x);

			right.x = cos(rotation.y) * cos(rotation.z);
			right.y = sin(rotation.z) * cos(rotation.y);
			right.z = sin(rotation.y) * cos(rotation.z);
			//right = _Vector3(forward.z, forward.x, forward.y);
			up = right * forward;*/
			_Vector3 forward_0, right_0, up_0, forward_1, right_1, up_1;
			_Vector3 f, r, u;
			r = _Vector3(1, 0, 0);
			u = _Vector3(0, cos(rotation.x), -1 * sin(rotation.x));
			f = _Vector3(0, sin(rotation.x), cos(rotation.x));

			forward_1 = _Vector3(_Vector3(0, 0, 1) >> r, _Vector3(0, 0, 1) >> u, _Vector3(0, 0, 1) >> f);
			right_1 = _Vector3(_Vector3(1, 0, 0) >> r, _Vector3(1, 0, 0) >> u, _Vector3(1, 0, 0) >> f);
			up_1 = _Vector3(_Vector3(0, 1, 0) >> r, _Vector3(0, 1, 0) >> u, _Vector3(0, 1, 0) >> f);

			r = _Vector3(cos(rotation.y), 0, sin(rotation.y));
			u = _Vector3(0, 1, 0);
			f = _Vector3(-1 * sin(rotation.y), 0, cos(rotation.y));

			forward_0 = _Vector3(forward_1 >> r, forward_1 >> u, forward_1 >> f);
			right_0 = _Vector3(right_1 >> r, right_1 >> u, right_1 >> f);
			up_0 = _Vector3(up_1 >> r, up_1 >> u, up_1 >> f);

			r = _Vector3(cos(rotation.z), -1 * sin(rotation.z), 0);
			u = _Vector3(sin(rotation.z), cos(rotation.z), 0);
			f = _Vector3(0, 0, 1);

			forward = _Vector3(forward_0 >> r, forward_0 >> u, forward_0 >> f);
			right = _Vector3(right_0 >> r, right_0 >> u, right_0 >> f);
			up = _Vector3(up_0 >> r, up_0 >> u, up_0 >> f);

			//forward = forward.normalize();
			//right = right.normalize();
			//up = up.normalize();
		}
		void LateUpdate() {}

		_Vector3 convertToLocalPosition(_Vector3 direction) {
			return(_Vector3(
				(direction - position) >> right,
				(direction - position) >> up,
				(direction - position) >> forward));
		}
	};

	class Triangle {
	public:
		List<_Vector3> vertices;
		Color color;
		double distFromCamera;
		Triangle reverse() {
			Triangle res = *this;
			res.vertices.insert(1, res.vertices.get(2));
			res.vertices.pop(3);
			return res;
		}

		_Vector3 normal;

		void recalculateNormal() {
			normal = (vertices.get(1) - vertices.get(0)) * (vertices.get(2) - vertices.get(0));
		}
	};

	class Mesh : public Component {
	public:
		List<Triangle> triangles;
		void Awake() { componentName = "Mesh"; }
		void Start() {}
		void Update() {}
		void LateUpdate() {}
	};

	class Light : public Component {
	public:
		double intensity;
		void Awake() { componentName = "Light"; }
		void Start() {}
		void Update() {}
		void LateUpdate() {}
	};

	class CameraScript : public Component {
	public:
		RenderWindow * window;
		Scene * thisScene;
		double angleK = 1.6f;
		void Start() {
			//cout << "Start" << endl;
		}

		void Awake() {
			componentName = "CameraScript";
			//cout << "Awake" << endl;
		}

		List<Triangle> sortByDist(List<Mesh*> data) {
			List<Triangle> first = List<Triangle>();
			for (int i = 0; i < data.length(); i++)
			{
				_Transform *currentTransform = data.get(i)->gameObject->GetComponent<_Transform>();
				for (int j = 0; j < data.get(i)->triangles.length(); j++)
				{
					Triangle current = Triangle();
					current.vertices.append(data.get(i)->triangles.get(j).vertices.get(0));
					current.vertices.append(data.get(i)->triangles.get(j).vertices.get(1));
					current.vertices.append(data.get(i)->triangles.get(j).vertices.get(2));
					current.color = data.get(i)->triangles.get(j).color;
					current.normal = data.get(i)->triangles.get(j).normal;
					for (int k = 0; k < 3; k++)
					{
						_Vector3 res = current.vertices.get(k) << currentTransform->scale;

						_Vector3 forward, right, up;
						right = _Vector3(1, 0, 0);
						up = _Vector3(0, cos(currentTransform->rotation.x), -1 * sin(currentTransform->rotation.x));
						forward = _Vector3(0, sin(currentTransform->rotation.x), cos(currentTransform->rotation.x));
						_Vector3 result_1 = _Vector3(res >> right, res >> up, res >> forward);

						right = _Vector3(cos(currentTransform->rotation.y), 0, sin(currentTransform->rotation.y));
						up = _Vector3(0, 1, 0);
						forward = _Vector3(-1 * sin(currentTransform->rotation.y), 0, cos(currentTransform->rotation.y));
						_Vector3 result_0 = _Vector3(result_1 >> right, result_1 >> up, result_1 >> forward);

						right = _Vector3(cos(currentTransform->rotation.z), -1 * sin(currentTransform->rotation.z), 0);
						up = _Vector3(sin(currentTransform->rotation.z), cos(currentTransform->rotation.z), 0);
						forward = _Vector3(0, 0, 1);
						_Vector3 result = _Vector3(result_0 >> right, result_0 >> up, result_0 >> forward);

						result = result + currentTransform->position;
						current.vertices.set(k, result);
					}
					_Vector3 middle = (current.vertices.get(0) + current.vertices.get(1) + current.vertices.get(2)) / 3.0f;
					current.distFromCamera = middle.distance(gameObject->GetComponent<_Transform>()->position);
					current.recalculateNormal();
					first.append(current);
				}
				//delete(currentTransform);
			}

			for (int i = 0; i < first.length(); i++)
			{
				for (int j = 0; j < first.length() - i - 1; j++)
				{
					if (first.get(j).distFromCamera < first.get(j + 1).distFromCamera) {
						Triangle current = first.get(j);
						first.get_(j)->value = first.get(j + 1);
						first.get_(j + 1)->value = current;
					}
				}
			}

			return(first);

		}

		void Update() {
			List<Mesh*> meshes = thisScene->getComponents<Mesh>();
			List<Light *>light = thisScene->getComponents<Light>();
			List<Triangle> sceneTriangles = sortByDist(meshes);
			//cout << sceneTriangles.length() << endl;;
			for (int i = 0; i < sceneTriangles.length(); i++)
			{

				_Vector3 normal = sceneTriangles.get(i).normal;

				_Vector3 middle = (sceneTriangles.get(i).vertices.get(0) +
					sceneTriangles.get(i).vertices.get(1) + sceneTriangles.get(i).vertices.get(2)) / 3;
				double k = 0;
				for (int p = 0; p < light.length(); p++)
				{
					double app = cos(normal.angle(light.get(p)->gameObject->GetComponent<_Transform>()->position -
						middle));
					if (app < 0) {
						app = 0;
					}
					app *= light.get(p)->intensity / pow(middle.distance(light.get(p)->gameObject->GetComponent<_Transform>()->
						position), 2);
					k += app;
				}

				//if (k < 0) {
				//	k = 0;
				//}
				//k *= light->intensity / pow(middle.distance(light->gameObject->GetComponent<_Transform>()->position), 2);
				int r, g, b;
				r = round(sceneTriangles.get(i).color.r * k);
				g = round(sceneTriangles.get(i).color.g * k);
				b = round(sceneTriangles.get(i).color.b * k);
				if (r > 255) {
					r = 255;
				}
				if (g > 255) {
					g = 255;
				}
				if (b > 255) {
					b = 255;
				}

				Color resultColor = Color(r, g, b);
				List<List<int>> positions = List<List<int>>();
				for (int l = 0; l < 3; l++)
				{
					_Vector3 localPos = this->gameObject->GetComponent<_Transform>()->convertToLocalPosition(sceneTriangles.get(i).vertices.get(l));
					List<int> pos = List<int>();
					int x = round(((localPos.x / localPos.z * angleK) + 0.5f) * H);
					int y = H - round(((localPos.y / localPos.z * angleK) + 0.5f) * H);
					pos.append(x);
					pos.append(y);
					if (localPos.z < 0.001f) {
						resultColor.a = 0;
					}
					positions.append(pos);
				}

				ConvexShape triangle;
				triangle.setPointCount(3);
				for (int l = 0; l < 3; l++)
				{
					triangle.setPoint(l, Vector2f(positions.get(l).get(0), positions.get(l).get(1)));
				}
				triangle.setFillColor(resultColor);
				//cout << (int)resultColor.r << " " << (int)resultColor.g  << " " << (int)resultColor.b << " " << (int)resultColor.a << endl;
				window->draw(triangle);



			}
		}

		void LateUpdate() {

		}
	};



#endif
