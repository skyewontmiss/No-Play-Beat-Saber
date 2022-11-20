#include "main.hpp"
// Think of these as C#, using MainMenuViewController, using UnityEngine.UI.Button, using HMUI.CurvedTextMeshPro ect.
// Classes without a namespace are assigned to the GlobalNamespace
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "GlobalNamespace/MusicPackPromoBanner.hpp"

//quest ui shit
#include "extern/includes/questui/shared/BeatSaberUI.hpp"
#include "extern/includes/questui/shared/QuestUI.hpp"

// Create a hook struct, named MainMenuUIHook.
// Target "void MainMenuViewController::DidActivate" and takes the following arguments:
// bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling

// General format: MAKE_HOOK_MATCH(HookName, method, method return type, method class pointer, arguments...) { 
//  HookName(arguments...);
//  // your code here 
//}

MAKE_HOOK_MATCH(FuckAllMenuButtons, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController
*self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{

    getLogger().info("Activate Fuck All Menu Buttons");
    // Run the original method before our code.
    // Note, you can run the original method after our code if you want to change arguments.
    FuckAllMenuButtons(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    // Get the _soloButton text using the dyn_ method and simple unity jazz. dyn_ safely get fields and shouldn't change
    // much during updates.
    auto objectThings = self->FindObjectsOfType<UnityEngine::GameObject *>();
   for (auto &go : objectThings)
    {
        auto menuThing = go->get_gameObject();
        std::string str = menuThing->GetName(menuThing);
        const char * c = str.c_str();
        getLogger().info("%s", c);
    }

    UnityEngine::UI::Button *soloMenuButton = self->dyn__soloButton();
    UnityEngine::GameObject *go1 = soloMenuButton->get_gameObject();
        go1->SetActive(false);
        getLogger().info("Successful get solo");
    UnityEngine::GameObject::Destroy(soloMenuButton);
    HMUI::CurvedTextMeshPro *soloMenuText = go1->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();
    // Set the text to "Skill Issue"
    soloMenuText->SetText("your bad at beat saber");

        UnityEngine::UI::Button *multiplayerMenuButton = self->dyn__multiplayerButton();
    UnityEngine::GameObject *go2 = multiplayerMenuButton->get_gameObject();
        go2->SetActive(false);
        getLogger().info("Successful get multi");
    UnityEngine::GameObject::Destroy(multiplayerMenuButton);
    HMUI::CurvedTextMeshPro *multiplayerMenuText = go2->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();
    // Set the text to "Skill Issue"
    multiplayerMenuText->SetText("you have no friends");

        UnityEngine::UI::Button *campaignMenuButton = self->dyn__campaignButton();
    UnityEngine::GameObject *go3 = campaignMenuButton->get_gameObject();
        getLogger().info("Successful get Gameobjects");
    go3->SetActive(false);
    HMUI::CurvedTextMeshPro *campaignMenuText = go3->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();
    // Set the text to "Skill Issue"
    campaignMenuText->SetText("Bro who even plays the campaign");

        UnityEngine::UI::Button *partyMenuButton = self->dyn__partyButton();
    UnityEngine::GameObject *go4 = partyMenuButton->get_gameObject();
        getLogger().info("Successful get Gameobjects");
    go4->SetActive(false);
    HMUI::CurvedTextMeshPro *partyMenuText = go4->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();
    // Set the text to "Skill Issue"
    partyMenuText->SetText("Party Mode is irrelevant");


        getLogger().info("party mode is irrelevant");

        //remove ad
    GlobalNamespace::MusicPackPromoBanner *AdButton = self->musicPackPromoBanner;
    UnityEngine::GameObject *gameObject = AdButton->get_gameObject();
    
    gameObject->SetActive(false);
}


static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    // Install our hooks (none defined yet)
      INSTALL_HOOK(getLogger(), FuckAllMenuButtons);
    getLogger().info("Installed all hooks!");
}
