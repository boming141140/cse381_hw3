// IN THIS FILE WE'LL BE DECLARING METHODS DECLARED INSIDE THIS HEADER FILE
#include "controller.hpp"

// OUR OWN TYPES
#include "scene_graph/components/aabb.hpp"
#include "scene_graph/components/mesh.hpp"
#include "scene_graph/event.hpp"
#include "scene_graph/node.hpp"
#include "scene_graph/script.hpp"
#include "core/renderer.hpp"
#include "scene_graph/scripts/player.hpp"
using namespace W3D::sg;

namespace W3D
{
// Class that is responsible for dispatching events and answering collision queries

Controller::Controller(sg::Node &camera_node, sg::Node &player_1_node, sg::Node &player_2_node, sg::Node &Light_1_node, sg::Node &Light_2_node, sg::Node &Light_3_node, sg::Node &Light_4_node) :
    camera_(camera_node),
    player_1(player_1_node),
    player_2(player_2_node),
    Light_1(Light_1_node),
    Light_2(Light_2_node),
    Light_3(Light_3_node),
    Light_4(Light_4_node)
{
}

void Controller::process_event(const Event &event)
{
	// IF IT'S A KEY PRESS WE NEED TO CHECK TO SEE IF WE SHOULD SWITCH MODES
	if (event.type == EventType::eKeyInput)
	{
		const auto &key_input_event = static_cast<const KeyInputEvent &>(event);
		// NUMBER KEYS ARE ALL GREATER
		if (key_input_event.code == KeyCode::eQ && key_input_event.action == KeyAction::eDown)
		{
			this->render->add_new_player();
			return;
		}
		else if (key_input_event.code == KeyCode::eR && key_input_event.action == KeyAction::eDown)
		{
			this->render->reload_scene("2.0/BoxTextured/glTF/HW.gltf");
			return;
		}
		else if (key_input_event.code == KeyCode::eF && key_input_event.action == KeyAction::eDown)
		{
			this->render->on_shoot();
		}
		else if (key_input_event.code > KeyCode::eD && key_input_event.action == KeyAction::eDown)
		{
			switch_mode(key_input_event.code);
			return;
		}
		
			
	}

	// DELIVER IT TO THE SCRIPT
	deliver_event(event);
}

void Controller::switch_mode(KeyCode code)
{
	player_shut_off();
	sg::Script *p_script;
	// THE 1 KEY SWITCHES CONTROL TO THE PLAYER 1 CUBE
	if (code == KeyCode::e1)
	{
		mode_ = ControllerMode::ePlayer1;
		p_script               = &player_1.get_component<sg::Script>();
		sg::Script *p_script_1 = &player_1.get_component<sg::Script>();
		Player     *p_player_1 = dynamic_cast<Player *>(p_script_1);
		p_player_1->toggle_select_on();
	}
	// THE 2 KEY SWITCHES CONTROL TO THE PLAYER 2 CUBE
	else if (code == KeyCode::e2)
	{
		mode_ = ControllerMode::ePlayer2;
		p_script               = &player_2.get_component<sg::Script>();
		sg::Script *p_script_2 = &player_2.get_component<sg::Script>();
		Player     *p_player_2 = dynamic_cast<Player *>(p_script_2);
		p_player_2->toggle_select_on();
	}
	// THE 3 KEY SWITCHES CONTROL TO THE CAMERA 
	else if (code == KeyCode::e3)
	{
		mode_ = ControllerMode::eCamera;
	}
	// THE 4 KEY SWITCHES CONTROL TO THE LIGHT 1 
	else if (code == KeyCode::e4)
	{
		mode_ = ControllerMode::eLight1;
	}
	// THE 5 KEY SWITCHES CONTROL TO THE LIGHT 2 
	else if (code == KeyCode::e5)
	{
		mode_ = ControllerMode::eLight2;
	}
	// THE 6 KEY SWITCHES CONTROL TO THE LIGHT 3 
	else if (code == KeyCode::e6)
	{
		mode_ = ControllerMode::eLight3;
	}
	// THE 7 KEY SWITCHES CONTROL TO THE LIGHT 4 
	else if (code == KeyCode::e7)
	{
		mode_ = ControllerMode::eLight4;
	}
	// THE 8 KEY SWITCHES CONTROL TO THE PLAYER 3 CUBE
	else if (code == KeyCode::e8)
	{
		mode_ = ControllerMode::ePlayer3;
		p_script               = &player_3->get_component<sg::Script>();
		sg::Script *p_script_3 = &player_3->get_component<sg::Script>();
		Player     *p_player_3 = dynamic_cast<Player *>(p_script_3);
		p_player_3->toggle_select_on();
	}
	// THE 9 KEY SWITCHES CONTROL TO THE PLAYER 4 CUBE
	else if (code == KeyCode::e9)
	{
		mode_ = ControllerMode::ePlayer4;
		p_script               = &player_4->get_component<sg::Script>();
		sg::Script *p_script_4 = &player_4->get_component<sg::Script>();
		Player     *p_player_4 = dynamic_cast<Player *>(p_script_4);
		p_player_4->toggle_select_on();
	}
	// THE 0 KEY SWITCHES CONTROL TO THE PLAYER 5 CUBE
	else if (code == KeyCode::e0)
	{
		mode_ = ControllerMode::ePlayer5;
		p_script               = &player_5->get_component<sg::Script>();
		sg::Script *p_script_5 = &player_5->get_component<sg::Script>();
		Player     *p_player_5 = dynamic_cast<Player *>(p_script_5);
		p_player_5->toggle_select_on();
	}
	
}

void Controller::deliver_event(const Event &event)
{
	// NOTIFY THE ASSOCIATED SCRIPT FOR THE GAME OBJECT SO IT CAN PROVIDE
	// A FURTHER REPONSE. FIRST GET THE ASSOCIATED SCRIPT
	
	sg::Script *p_script;
	if (mode_ == ControllerMode::ePlayer1)
	{
		p_script = &player_1.get_component<sg::Script>();
	}
	else if (mode_ == ControllerMode::ePlayer2)
	{
		p_script = &player_2.get_component<sg::Script>();
	}
	else if (mode_ == ControllerMode::eCamera)
	{
		p_script = &camera_.get_component<sg::Script>();
	}
	else if (mode_ == ControllerMode::eLight1)
	{
		p_script = &Light_1.get_component<sg::Script>();
	}
	else if (mode_ == ControllerMode::eLight2)
	{
		p_script = &Light_2.get_component<sg::Script>();
	}
	else if (mode_ == ControllerMode::eLight3)
	{
		p_script = &Light_3.get_component<sg::Script>();
	}
	else if (mode_ == ControllerMode::eLight4)
	{
		p_script = &Light_4.get_component<sg::Script>();
	}
	else if (mode_ == ControllerMode::ePlayer3 && player_3 != nullptr)
	{
		p_script = &player_3->get_component<sg::Script>();
	}
	else if (mode_ == ControllerMode::ePlayer4 && player_4 != nullptr)
	{
		p_script = &player_4->get_component<sg::Script>();
	}
	else if (mode_ == ControllerMode::ePlayer5 && player_5 != nullptr)
	{
		p_script = &player_5->get_component<sg::Script>();
	}
	else
	{
		p_script = &camera_.get_component<sg::Script>();
	}
	// AND NOW ASK THE SCRIPT TO PROVIDE A PROGRAMMED RESPONSE
	p_script->process_event(event);
}

void Controller::player_shut_off()
{
	sg::Script *p_script_1 = &player_1.get_component<sg::Script>();
	sg::Script *p_script_2 = &player_2.get_component<sg::Script>();

	Player *p_player_1 = dynamic_cast<Player *>(p_script_1);
	Player *p_player_2 = dynamic_cast<Player *>(p_script_2);
	if (player_5)
	{
		sg::Script *p_script_3 = &player_3->get_component<sg::Script>();
		sg::Script *p_script_4 = &player_4->get_component<sg::Script>();
		sg::Script *p_script_5 = &player_5->get_component<sg::Script>();

		Player *p_player_3 = dynamic_cast<Player *>(p_script_3);
		Player *p_player_4 = dynamic_cast<Player *>(p_script_4);
		Player *p_player_5 = dynamic_cast<Player *>(p_script_5);
		p_player_3->toggle_select_off();
		p_player_4->toggle_select_off();
		p_player_5->toggle_select_off();
	}
	if (player_4)
	{
		sg::Script *p_script_3 = &player_3->get_component<sg::Script>();
		sg::Script *p_script_4 = &player_4->get_component<sg::Script>();

		Player *p_player_3 = dynamic_cast<Player *>(p_script_3);
		Player *p_player_4 = dynamic_cast<Player *>(p_script_4);

		p_player_3->toggle_select_off();
		p_player_4->toggle_select_off();
	}
	if (player_3)
	{
		sg::Script *p_script_3 = &player_3->get_component<sg::Script>();

		Player *p_player_3 = dynamic_cast<Player *>(p_script_3);

		p_player_3->toggle_select_off();
	}
	p_player_1->toggle_select_off();
	p_player_2->toggle_select_off();
}
bool Controller::are_players_colliding(sg::Node &node)
{
	glm::mat4 p1_M              = player_1.get_transform().get_world_M();
	glm::mat4 p2_M              = player_2.get_transform().get_world_M();
	glm::mat4 p3_M              = glm::mat4(0.0f);
	glm::mat4 p4_M              = glm::mat4(0.0f);
	glm::mat4 p5_M              = glm::mat4(0.0f);
	
	
	sg::AABB  p1_transformed_bd = player_1.get_component<sg::Mesh>().get_bounds().transform(p1_M);
	sg::AABB  p2_transformed_bd = player_2.get_component<sg::Mesh>().get_bounds().transform(p2_M);
	sg::AABB  p3_transformed_bd;
	sg::AABB  p4_transformed_bd;
	sg::AABB  p5_transformed_bd;
	
	sg::AABB holder;
	std::vector<sg::AABB> transformedBounds;
	if (node.get_name() == "player_1")
		holder = p1_transformed_bd;
	else
		transformedBounds.push_back(p1_transformed_bd);
	if (node.get_name() == "player_2")
		holder = p2_transformed_bd;
	else
		transformedBounds.push_back(p2_transformed_bd);
	if (player_3)
	{
		p3_M              = player_3->get_transform().get_world_M();
		p3_transformed_bd = player_3->get_component<sg::Mesh>().get_bounds().transform(p3_M);
		if (node.get_name() != "player_3")
			transformedBounds.push_back(p3_transformed_bd);
		else
			holder = p3_transformed_bd;
	}
	if (player_4)
	{
		p4_M              = player_4->get_transform().get_world_M();
		p4_transformed_bd = player_4->get_component<sg::Mesh>().get_bounds().transform(p4_M);
		if (node.get_name() != "player_4")
			transformedBounds.push_back(p4_transformed_bd);
		else
			holder = p4_transformed_bd;
	}
	if (player_5)
	{
		p5_M              = player_5->get_transform().get_world_M();
		p5_transformed_bd = player_5->get_component<sg::Mesh>().get_bounds().transform(p5_M);
		if (node.get_name() != "player_5")
			transformedBounds.push_back(p5_transformed_bd);
		else
			holder = p5_transformed_bd;
	}
	
	bool result = false;
	for (auto it = transformedBounds.begin(); it != transformedBounds.end(); ++it)
	{
		result = result || holder.collides_with(*it);
	}
	return result;
}

void Controller::insert_render(Renderer &render)
{
	this->render = &render;
}

void Controller::insert_player_3(sg::Node &new_player_3)
{
	this->player_3 = &new_player_3;
}

void Controller::insert_player_4(sg::Node &new_player_4)
{
	this->player_4 = &new_player_4;
}

void Controller::insert_player_5(sg::Node &new_player_5)
{
	this->player_5 = &new_player_5;
}


};        // namespace W3D