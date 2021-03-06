#include "../include/Interface.hpp"

/********************************
 *        IMGUI INTERFACE       *
 ********************************/

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

Interface::Interface() : windowManager(SDLWindowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "World IMaker"))
{
	// Initialize Glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError)
    {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        std::exit(0);
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(windowManager.window, windowManager.openglContext);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();
}

void Interface::startFrame() const
{
	// Clear context
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.1, 1.0);

    // Calling new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(windowManager.window);
    ImGui::NewFrame();
}

void Interface::editCube(Cubes &cube, Curseur &cursor, Map &map) const
{
	// Settings
	ImGui::SetNextWindowPos(ImVec2(10, 150));
	ImGui::SetNextWindowSize(ImVec2(260, 250));
    
    // Set colors
	std::vector<glm::vec4> allColors = {glm::vec4(0.8, 0.2, 0.3, 1.0), glm::vec4(0.3, 0.8, 0.2, 1.0), glm::vec4(0.2, 0.3, 0.8, 1.0)};
	glm::vec4 defaultColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
	int defaultType = 0;

	// Create menu with options
	ImGui::Begin("Options : Cube / Colonne");	

		ImGui::Text("Modifier la couleur du cube :");
	        static int selected = -1;
			char buf[32];
			// color 1
	        sprintf(buf, "%d - Rouge", 1);
	        if (ImGui::Selectable(buf, selected == 0))
	        {
	            selected = 0;
	            cube.editColor(cursor.getPosition(), allColors[0]);
	        }
	        // color 2
	        sprintf(buf, "%d - Vert", 2);
	        if (ImGui::Selectable(buf, selected == 1))
	        {
	            selected = 1;
	            cube.editColor(cursor.getPosition(), allColors[1]);
	        }
	        // color 3
	        sprintf(buf, "%d - Bleu", 3);
	        if (ImGui::Selectable(buf, selected == 2))
	        {
	            selected = 2;
	            cube.editColor(cursor.getPosition(), allColors[2]);
	        }

	        if(selected == 0) defaultColor = allColors[0];
	        if(selected == 1) defaultColor = allColors[1];
	        if(selected == 2) defaultColor = allColors[2];
		ImGui::Text(" ");

		ImGui::Text("Action pour un cube :");
			if (ImGui::Button("  Créer cube   "))
			{
				cube.addCube(cursor.getPosition(), defaultColor, defaultType);
			}

			ImGui::SameLine();

			if (ImGui::Button(" Supprimer cube "))
			{
				cube.removeCube(cursor.getPosition());
			}
		ImGui::Text(" ");
		
		ImGui::Text("Action sur une colonne :");
			if (ImGui::Button("Extrude colonne")) {
				glm::vec4 localizedColor = defaultColor;
				int localizedType = defaultType;
				if (cube.findCube(cursor.getPosition()) != -1) {
					localizedColor = cube.getColors()[cube.findCube(cursor.getPosition())];
				}
				cube.extrudeCube(cursor.getPosition(), localizedColor, localizedType);
			}

			ImGui::SameLine();

			if (ImGui::Button("  Dig  colonne  ")) {
				if (cube.findCube(cursor.getPosition()) != -1) {
					cube.digCube(cursor.getPosition());
				}
			}
		ImGui::Text(" ");
		editMap(cube, map, defaultColor);
		editScene(cube, map);
		
	ImGui::End();
}

void Interface::editMap(Cubes &cube, Map &map, glm::vec4 defaultColor) const
{
	// Settings
	ImGui::SetNextWindowPos(ImVec2(10, 410));
	ImGui::SetNextWindowSize(ImVec2(260, 185));

	// Create menu with options
	ImGui::Begin("Génération procédurale :");
		static int flag = 0;
		if (ImGui::Button("    Activer    ")){
			map.loadWorld(cube, defaultColor);
			flag = 1;
			std::cout<< "Génération procédurale activée"<<std::endl;
		}
		ImGui::SameLine();
		if (ImGui::Button("   Désactiver   ")){
			map.clearWorld(cube);
			flag = 0;
			std::cout<< "Génération procédurale désactivée"<<std::endl;
		}

		ImGui::Text(" ");
		ImGui::Text("Action sur un point de controle :");
		static int poids = 0, x = 20, z = 20;
		ImGui::SliderInt("Position x", &x, 0, 20);
		ImGui::SliderInt("Position z", &z, 0, 20);
		ImGui::SliderInt("Poids", &poids, 0, 20);

		if (ImGui::Button("    Ajouter    ")){
			if((x < 21) && (x > -1) && (z < 21) && (z > -1) && (poids > 0) && (poids < 21))
				map.addControlPoint(x, z, poids);
			else 
				std::cerr<< "ERREUR : vos valeurs doivent se situer entre 0 et 20"<<std::endl;
			if (flag == 1)
				map.loadWorld(cube, defaultColor);
		}
		ImGui::SameLine();
		if (ImGui::Button("   Supprimer   ")){
			map.removeControlPoint((float)x, (float)z);
			if (flag == 1)
				map.loadWorld(cube, defaultColor);
		}

	ImGui::End();

}

void Interface::editScene(Cubes &cube, Map &map) const
{
	// Settings
	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::SetNextWindowSize(ImVec2(260, 130));

	ImGui::Begin("Scène 3D :");

		if (ImGui::Button(" Scène initiale "))
		{
			map.initWorld(cube);
		}

		ImGui::SameLine();

		if (ImGui::Button(" Tout supprimer "))
		{
			map.deleteInitWorld(cube);
		}
		ImGui::Text(" ");

		ImGui::Text("Scène actuelle :");
		if (ImGui::Button("  Sauvegarder  "))
		{
			std::string filename, filepath;
			std::cout << "Nom du fichier (ex : test) : ";
			std::cin >> filename;
			std::cout << "Emplacement (ex : /home/user/Documents/) : ";
			std::cin >> filepath;
			cube.saveScene(filepath, filename);
		}

		ImGui::SameLine();

		if (ImGui::Button("    Charger    "))
		{
			std::string filename, filepath;
			std::cout << "Nom du fichier (ex : test) : ";
			std::cin >> filename;
			std::cout << "Emplacement (ex : /home/user/Documents/) : ";
			std::cin >> filepath;
			cube.loadScene(filepath, filename);
		}
	
	ImGui::End();	
}

void Interface::endFrame() const
{
	// Update the display
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(windowManager.window);
}

Interface::~Interface()
{
	// Clean up ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // Clean up SDL / OpenGL
    SDL_GL_DeleteContext(windowManager.openglContext);
    SDL_DestroyWindow(windowManager.window);
    SDL_Quit();
}