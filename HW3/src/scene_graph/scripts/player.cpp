// IN THIS FILE WE'LL BE DECLARING METHODS DECLARED INSIDE THIS HEADER FILE
#include "player.hpp"

namespace W3D::sg
{

const float Player::TRANSLATION_MOVE_STEP = 5.0f;

Player::Player(Node &node) :
    NodeScript(node)
{
}

// This method is called every frame. Responsible for updating a node's state
void Player::update(float delta_time)
{
	glm::vec3 delta_translation(0.0f, 0.0f, 0.0f);

	// Caveat: The models are rotated! Therefore, we translate the objects in model space in z-direction
	if (key_pressed_[KeyCode::eW])
	{
		delta_translation.z += TRANSLATION_MOVE_STEP;
	}

	if (key_pressed_[KeyCode::eS])
	{
		delta_translation.z -= TRANSLATION_MOVE_STEP;
	}

	if (key_pressed_[KeyCode::eA])
	{
		delta_translation.x -= TRANSLATION_MOVE_STEP;
	}

	if (key_pressed_[KeyCode::eD])
	{
		delta_translation.x += TRANSLATION_MOVE_STEP;
	}
	
	if (selected && get_node().get_children().size() != 0)
	{
		pryamid_rotate(delta_time);
	}

	// WE NEED TO SCALE BECAUSE WE HAVE A VARIABLE TIMER
	delta_translation *= speed_multiplier_ * delta_time;

	// UPDATE THE TRANSFORMATION VECTOR FOR THIS NODE
	auto &G = get_node();
	auto &T = get_node().get_transform();
	T.set_tranlsation(T.get_translation() + delta_translation);
	
	//glm::vec3 new_delta_translation = glm::vec3(0.0f, 2.0f, 0.0f);
	if (get_node().get_children().size() != 0)
	{
		get_node().get_children()[0]->get_transform().invalidate_local_M();
		//B.set_tranlsation(T.get_translation() + new_delta_translation);
	}
	
	
}
void Player::pryamid_rotate(float delta_time)
{
	auto     &temp1            = get_node();
	auto &temp = get_node().get_children()[0];
	double    rotationAngle    = 0.0;
	glm::vec3 center           = glm::vec3(0);
	glm::vec3 pyramid_location = get_node().get_children()[0]->get_transform().get_translation();
	double    rotationSpeed    = 1;

	// Update the rotation angle
	rotationAngle += rotationSpeed * delta_time;

	// Calculate the radius of the orbit
	glm::vec3 orbitVector = pyramid_location - center;
	float     radius      = glm::length(orbitVector);

	// Calculate the current angle
	float currentAngle = atan2(orbitVector.y, orbitVector.x);

	// Update the angle with the rotation
	float newAngle = currentAngle + rotationAngle;

	// Calculate new position
	glm::vec3 newPyramidLocation;
	newPyramidLocation.x = center.x + radius * cos(newAngle);
	newPyramidLocation.y = center.y + radius * sin(newAngle);        // Assuming the rotation is in the XZ plane
	newPyramidLocation.z = pyramid_location.z;    

	get_node().get_children()[0]->get_transform().set_tranlsation(newPyramidLocation);
}
void Player::process_event(const Event &event)
{
	if (event.type == EventType::eKeyInput)
	{
		const auto &key_event = static_cast<const KeyInputEvent &>(event);

		// WE DO THIS SO WE CAN RESPOND TO HOLDING DOWN A KEY FOR MULTIPLE FRAMES
		// WHICH WE THEN DO INSIDE THE update FUNCTION
		if (key_event.action == KeyAction::eDown || key_event.action == KeyAction::eRepeat)
		{
			key_pressed_[key_event.code] = true;
		}
		else
		{
			key_pressed_[key_event.code] = false;
		}

	}
}

void Player::toggle_select_off()
{
	selected = false;
}

void Player::toggle_select_on()
{
	selected = true;
}

}	// namespace W3D::sg