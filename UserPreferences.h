#ifndef USERPREFERENCES
#define USERPREFERENCES

#include "Engine.h"
#include "Import.h"
#include "UI.h"


class PlayerController : public Component {
public:
	double speed = 1.5f;
	double frameTime = 0.02f;
	double rotationSpeed = 0.9f;
	void Start() {}
	void Awake() {}
	void Update() {
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			gameObject->GetComponent<_Transform>()->position = gameObject->GetComponent<_Transform>()->position + (gameObject->GetComponent<_Transform>()->forward * speed * frameTime);
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			gameObject->GetComponent<_Transform>()->position = gameObject->GetComponent<_Transform>()->position - (gameObject->GetComponent<_Transform>()->forward * speed * frameTime);
		}
		if (Keyboard::isKeyPressed(Keyboard::Q)) {
			gameObject->GetComponent<_Transform>()->rotation.y = gameObject->GetComponent<_Transform>()->rotation.y - rotationSpeed * frameTime;
		}
		if (Keyboard::isKeyPressed(Keyboard::E)) {
			gameObject->GetComponent<_Transform>()->rotation.y = gameObject->GetComponent<_Transform>()->rotation.y + rotationSpeed * frameTime;
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			gameObject->GetComponent<_Transform>()->position = gameObject->GetComponent<_Transform>()->position - (gameObject->GetComponent<_Transform>()->right * speed * frameTime);
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			gameObject->GetComponent<_Transform>()->position = gameObject->GetComponent<_Transform>()->position + (gameObject->GetComponent<_Transform>()->right * speed * frameTime);
		}

		if (Keyboard::isKeyPressed(Keyboard::Z)) {
			gameObject->GetComponent<_Transform>()->rotation.x = gameObject->GetComponent<_Transform>()->rotation.x - rotationSpeed * frameTime;
		}

		if (Keyboard::isKeyPressed(Keyboard::X)) {
			gameObject->GetComponent<_Transform>()->rotation.x = gameObject->GetComponent<_Transform>()->rotation.x + rotationSpeed * frameTime;
		}
	}
	void LateUpdate() {}
};

class CubeScript : public Component {
public:
	double speed = 0.01f;
	void Start() {}
	void Awake() {}
	void LateUpdate() {}
	void Update() {
		if (Keyboard::isKeyPressed(Keyboard::R)) {
			gameObject->GetComponent<_Transform>()->rotation.y += speed;
		}
		if (Keyboard::isKeyPressed(Keyboard::T)) {
			gameObject->GetComponent<_Transform>()->rotation.y -= speed;
		}

		if (Keyboard::isKeyPressed(Keyboard::F)) {
			gameObject->GetComponent<_Transform>()->rotation.x += speed;
		}
		if (Keyboard::isKeyPressed(Keyboard::G)) {
			gameObject->GetComponent<_Transform>()->rotation.x -= speed;
		}

		if (Keyboard::isKeyPressed(Keyboard::C)) {
			gameObject->GetComponent<_Transform>()->rotation.z += speed;
		}
		if (Keyboard::isKeyPressed(Keyboard::V)) {
			gameObject->GetComponent<_Transform>()->rotation.z -= speed;
		}
	}
};
Scene mainScene = Scene();

int num = 0;




void change() {
	string * file = new string[3];
	file[0] = "Assets\\monkey_decimated_1.obj";
	file[1] = "Assets\\cube.obj";
	file[2] = "Assets\\sphere_decimated_2.obj";
	List<Mesh *> meshes = mainScene.getComponents<Mesh>();
	//cout << meshes.length();
	for (int i = 0; i < meshes.length(); i++)
	{
		GameObject *go = meshes.get(i)->gameObject;
		Mesh a = importAssetMesh(/*files.get(num%files.length())*/file[num%3]);
		//a.gameObject = go;
		meshes.get(i)->triangles = a.triangles;
		//meshes.get_(i)->value = &a;
	}
	num++;
	//cout << "Click" << endl;
}

void initializeGame() {
	
	//An object of RenderWindow class - main window
	RenderWindow window({ (unsigned int)W, (unsigned int)H }, "Engine", sf::Style::Close);
	window.setFramerateLimit(120);
	//Console window
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOW);

	
	mainScene.window = &window;

	
	//Generating cam
	GameObject Camera = GameObject();
	CameraScript camScript = CameraScript();
	camScript.thisScene = &mainScene;
	camScript.gameObject = &Camera;
	camScript.window = &window;
	Camera.components.append(&camScript);
	_Transform camTransform = _Transform();
	camTransform.gameObject = &Camera;
	camTransform.position = _Vector3(0, 1.0f, -5);
	Camera.components.append(&camTransform);
	PlayerController camControl = PlayerController();
	camControl.gameObject = &Camera;
	Camera.components.append(&camControl);

	Light light = Light();
	light.intensity = 100;
	light.gameObject = &Camera;
	Camera.components.append(&light);
	

	//Generating cube
	GameObject Cube = GameObject();
	//Generating mesh
	Mesh cubeMesh = importAssetMesh("Assets\\monkey_decimated_1.obj");
	/*List<Triangle> triangles;
	int quality = 1;
	int size = 8;
	for (int t = 0; t < quality; t++)
	{
		for (int p = 0; p < quality; p++)
		{
			for (int m = 0; m < quality; m++)
			{

				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						for (int k = 0; k < 2; k++)
						{
							//triangles.append(Triangle());
							_Vector3 A = _Vector3(i, j, k);
							_Vector3 B = _Vector3(i, j, 1 - k);
							_Vector3 C = _Vector3(i, 1 - j, k);
							_Vector3 D = _Vector3(1 - i, j, k);
							triangles.append(Triangle());
							ListE<Triangle> * current = triangles.get_(3 * (i * 4 + j * 2 + k) + 3 * (quality*(quality*t + p) + m)*size);
							current->value.vertices.append(A);
							current->value.vertices.append(B);
							current->value.vertices.append(C);
							current->value.recalculateNormal();
							if ((current->value.normal >> (_Vector3(0.5f, 0.5f, 0.5f) - A)) > 0) {
								current->value.reverse();
								current->value.recalculateNormal();
							}

							if ((current->value.normal >> _Vector3(0, 0, 1) < -0.01f)) {
								current->value.color = Color(128, 1, 1);
							}
							else
							{
								if ((current->value.normal >> _Vector3(0, 1, 0) < -0.01f)) {
									current->value.color = Color(1, 1, 128);
								}
								else
								{
									current->value.color = Color(1, 128, 1);
								}
							}
							for (int s = 0; s < 3; s++)
							{
								current->value.vertices.set(s, current->value.vertices.get(s) + _Vector3(t, p, m));
							}
							current->value.recalculateNormal();

							triangles.append(Triangle());
							current = triangles.get_(3 * (i * 4 + j * 2 + k) + 1 + (quality*(quality*t + p) + m)*size);
							current->value.vertices.append(A);
							current->value.vertices.append(B);
							current->value.vertices.append(D);
							current->value.recalculateNormal();
							if ((current->value.normal >> (_Vector3(0.5f, 0.5f, 0.5f) - A)) > 0) {
								current->value.reverse();
								current->value.recalculateNormal();
							}

							if ((current->value.normal >> _Vector3(0, 0, 1) < -0.01f)) {
								current->value.color = Color(128, 1, 1);
							}
							else
							{
								if ((current->value.normal >> _Vector3(0, 1, 0) < -0.01f)) {
									current->value.color = Color(1, 1, 128);
								}
								else
								{
									current->value.color = Color(1, 128, 1);
								}
							}
							for (int s = 0; s < 3; s++)
							{
								current->value.vertices.set(s, current->value.vertices.get(s) + _Vector3(t, p, m));
							}
							current->value.recalculateNormal();

							triangles.append(Triangle());
							current = triangles.get_(3 * (i * 4 + j * 2 + k) + 2 + (quality*(quality*t + p) + m)*size);
							current->value.vertices.append(A);
							current->value.vertices.append(D);
							current->value.vertices.append(C);
							current->value.recalculateNormal();
							if ((current->value.normal >> (_Vector3(0.5f, 0.5f, 0.5f) - A)) > 0) {
								current->value.reverse();
								current->value.recalculateNormal();
							}

							if ((current->value.normal >> _Vector3(0, 0, 1) < -0.01f)) {
								current->value.color = Color(128, 1, 1);
							}
							else
							{
								if ((current->value.normal >> _Vector3(0, 1, 0) < -0.01f)) {
									current->value.color = Color(1, 1, 128);
								}
								else
								{
									current->value.color = Color(1, 128, 1);
								}
							}
							for (int s = 0; s < 3; s++)
							{
								current->value.vertices.set(s, current->value.vertices.get(s) + _Vector3(t, p, m));
							}
							current->value.recalculateNormal();
						}

					}
				}
			}
		}
	}*/
	cout << cubeMesh.triangles.length();
	cubeMesh.gameObject = &Cube;
	Cube.components.append(&cubeMesh);
	_Transform cubeTransform = _Transform();
	cubeTransform.position = _Vector3(0.0f, 0, 0);
	cubeTransform.rotation = _Vector3(0.0f, 0.0f, 0);
	cubeTransform.scale = _Vector3(1, 1, 1);
	Cube.components.append(&cubeTransform);
	CubeScript cubeController = CubeScript();
	cubeController.gameObject = &Cube;
	Cube.components.append(&cubeController);
	//Adding objects to the scene
	mainScene.objects.append(Cube);

	GameObject ui = GameObject();
	Button buttonScript = Button();
	Texture t;
	t.loadFromFile("Assets\\button.png");

	Texture tp;
	tp.loadFromFile("Assets\\button_pressed.png");
	Font style;
	style.loadFromFile("Assets\\Sh.otf");
	buttonScript.set(Vector2f(100, 100), Vector2f(1, 1), Color(), t, tp, style, Sprite(), (Vector2f)window.getPosition(), L"Change", 30);
	
	buttonScript.gameObject = &ui;
	buttonScript.onClick = &change;
	buttonScript.window = &window;
	ui.components.append(&buttonScript);

	mainScene.objects.append(Camera);
	
	mainScene.objects.append(ui);
	
	//mainScene.objects.append(Lightning);
	
	//Use not more than 1000 vertices
	//starting
	mainScene.PLAY();
}



#endif
