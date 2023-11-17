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
#include <map>
using namespace W3D::sg;

namespace W3D
{
// Class that is responsible for dispatching events and answering collision queries

Controller::Controller(sg::Node &camera_node, sg::Node *player_1_node, sg::Node *player_2_node, sg::Node &Light_1_node, sg::Node &Light_2_node, sg::Node &Light_3_node, sg::Node &Light_4_node):
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
			this->render->shoot_bullet();
			return;
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
	if (code == KeyCode::e1 && player_1)
	{
		mode_ = ControllerMode::ePlayer1;
		p_script               = &player_1->get_component<sg::Script>();
		sg::Script *p_script_1 = &player_1->get_component<sg::Script>();
		Player     *p_player_1 = dynamic_cast<Player *>(p_script_1);
		p_player_1->toggle_select_on();
	}
	// THE 2 KEY SWITCHES CONTROL TO THE PLAYER 2 CUBE
	else if (code == KeyCode::e2 && player_2)
	{
		mode_ = ControllerMode::ePlayer2;
		p_script               = &player_2->get_component<sg::Script>();
		sg::Script *p_script_2 = &player_2->get_component<sg::Script>();
		Player     *p_player_2 = dynamic_cast<Player *>(p_script_2);
		p_player_2->toggle_select_on();
	}
	// THE 3 KEY SWITCHES CONTROL TO THE CAMERA 
	else if (code == KeyCode::e3 )
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
	else if (code == KeyCode::e8 && player_3)
	{
		mode_ = ControllerMode::ePlayer3;
		p_script               = &player_3->get_component<sg::Script>();
		sg::Script *p_script_3 = &player_3->get_component<sg::Script>();
		Player     *p_player_3 = dynamic_cast<Player *>(p_script_3);
		p_player_3->toggle_select_on();
	}
	// THE 9 KEY SWITCHES CONTROL TO THE PLAYER 4 CUBE
	else if (code == KeyCode::e9 && player_4)
	{
		mode_ = ControllerMode::ePlayer4;
		p_script               = &player_4->get_component<sg::Script>();
		sg::Script *p_script_4 = &player_4->get_component<sg::Script>();
		Player     *p_player_4 = dynamic_cast<Player *>(p_script_4);
		p_player_4->toggle_select_on();
	}
	// THE 0 KEY SWITCHES CONTROL TO THE PLAYER 5 CUBE
	else if (code == KeyCode::e0 && player_5)
	{
		mode_ = ControllerMode::ePlayer5;
		p_script               = &player_5->get_component<sg::Script>();
		sg::Script *p_script_5 = &player_5->get_component<sg::Script>();
		Player     *p_player_5 = dynamic_cast<Player *>(p_script_5);
		p_player_5->toggle_select_on();
	}
	else
	{
		mode_ = ControllerMode::eCamera;
	}
	
}

void Controller::deliver_event(const Event &event)
{
	// NOTIFY THE ASSOCIATED SCRIPT FOR THE GAME OBJECT SO IT CAN PROVIDE
	// A FURTHER REPONSE. FIRST GET THE ASSOCIATED SCRIPT
	
	sg::Script *p_script;
	if (mode_ == ControllerMode::ePlayer1 && player_1)
	{
		p_script = &player_1->get_component<sg::Script>();
	}
	else if (mode_ == ControllerMode::ePlayer2 && player_2)
	{
		p_script = &player_2->get_component<sg::Script>();
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
	else if (mode_ == ControllerMode::ePlayer3 && player_3)
	{
		p_script = &player_3->get_component<sg::Script>();
	}
	else if (mode_ == ControllerMode::ePlayer4 && player_4)
	{
		p_script = &player_4->get_component<sg::Script>();
	}
	else if (mode_ == ControllerMode::ePlayer5 && player_5)
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
	
	if (player_1)
	{
		sg::Script *p_script_1 = &player_1->get_component<sg::Script>();

		Player *p_player_1 = dynamic_cast<Player *>(p_script_1);

		p_player_1->toggle_select_off();
	}
	if (player_2)
	{
		sg::Script *p_script_2 = &player_2->get_component<sg::Script>();

		Player *p_player_2 = dynamic_cast<Player *>(p_script_2);

		p_player_2->toggle_select_off();
	}
	if (player_5)
	{
		sg::Script *p_script_5 = &player_5->get_component<sg::Script>();

		Player *p_player_5 = dynamic_cast<Player *>(p_script_5);
		
		p_player_5->toggle_select_off();
	}
	if (player_4)
	{
		
		sg::Script *p_script_4 = &player_4->get_component<sg::Script>();

		Player *p_player_4 = dynamic_cast<Player *>(p_script_4);

		p_player_4->toggle_select_off();
	}
	if (player_3)
	{
		sg::Script *p_script_3 = &player_3->get_component<sg::Script>();

		Player *p_player_3 = dynamic_cast<Player *>(p_script_3);

		p_player_3->toggle_select_off();
	}
}
bool Controller::are_players_colliding(sg::Node &node)
{
	std::vector<sg::Node *> players = {player_1, player_2, player_3, player_4, player_5};

	glm::mat4 node_transform = node.get_transform().get_world_M();
	sg::AABB  holder         = node.get_component<sg::Mesh>().get_bounds().transform(node_transform);

	std::vector<Bullet> bullet_vector = render->activeBullets;
	auto                it            = bullet_vector.begin();
	while (it != bullet_vector.end())
	{
		Bullet &bullet      = *it;
		Node   *bullet_node = bullet.node;
		if (bullet_node != &node)
		{
			glm::mat4 bullet_transform      = bullet_node->get_transform().get_world_M();
			sg::AABB  bullet_transformed_bd = bullet_node->get_component<sg::Mesh>().get_bounds().transform(bullet_transform);
			// Check for collision with the current node
			if (holder.collides_with(bullet_transformed_bd))
			{
				return true;
			}
		}
		++it;
	}
	// Process each player
	for (auto player : players)
	{
		// Check if the player is valid and not the node itself
		if (player && player->get_name() != node.get_name())
		{
			glm::mat4 transform      = player->get_transform().get_world_M();
			sg::AABB  transformed_bd = player->get_component<sg::Mesh>().get_bounds().transform(transform);

			// Check for collision with the current node
			if (holder.collides_with(transformed_bd))
			{
				return true;
			}
		}
	}

	// No collision found, return false
	return false;
}

sg::Node *Controller::colliding_target(sg::Node &node)
{
	std::vector<sg::Node *> players = {player_1, player_2, player_3, player_4, player_5};

	glm::mat4 node_transform      = node.get_transform().get_world_M();
	sg::AABB  holder         = node.get_component<sg::Mesh>().get_bounds().transform(node_transform);
	
	std::vector<Bullet> bullet_vector = render->activeBullets;
	auto                it            = bullet_vector.begin();
	while (it != bullet_vector.end())
	{
		Bullet &bullet      = *it;
		Node   *bullet_node = bullet.node;
		if (bullet_node != &node)
		{
			glm::mat4 bullet_transform      = bullet_node->get_transform().get_world_M();
			sg::AABB  bullet_transformed_bd = bullet_node->get_component<sg::Mesh>().get_bounds().transform(bullet_transform);
			// Check for collision with the current node
			if (holder.collides_with(bullet_transformed_bd))
			{
				return bullet_node;
			}
		}
		++it;
	}
	// Process each player
	for (auto player : players)
	{
		// Check if the player is valid and not the node itself
		if (player && player->get_name() != node.get_name())
		{
			glm::mat4 transform      = player->get_transform().get_world_M();
			sg::AABB  transformed_bd = player->get_component<sg::Mesh>().get_bounds().transform(transform);

			// Check for collision with the current node
			if (holder.collides_with(transformed_bd))
			{
				return player;
			}
		}
	}

	// No collision found, return nullptr
	return nullptr;
	
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

void Controller::delete_player(sg::Node& new_player_5)
{
	sg::Node **players[] = {&player_1, &player_2, &player_3, &player_4, &player_5};
	for (auto &player : players)
	{
		if (*player && *player == &new_player_5)
		{
			*player = nullptr;        // Set to nullptr to avoid dangling pointer
			break;                   // Assuming only one player can match
		}
	}
}
};        // namespace W3D