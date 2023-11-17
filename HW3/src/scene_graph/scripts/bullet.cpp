#include "bullet.hpp"

namespace W3D::sg
{

Bullet::Bullet(Node &node) :
    NodeScript(node)
{
}

// This method is called every frame. Responsible for updating a node's state
void Bullet::update(float delta_time)
{
	glm::vec3 delta_translation(0.0f, 0.0f, 0.0f);

	// Caveat: The models are rotated! Therefore, we translate the objects in model space in z-direction
	/* if (key_pressed_[KeyCode::eW])
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
	}*/

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

	// glm::vec3 new_delta_translation = glm::vec3(0.0f, 2.0f, 0.0f);
	if (get_node().get_children().size() != 0)
	{
		get_node().get_children()[0]->get_transform().invalidate_local_M();
		// B.set_tranlsation(T.get_translation() + new_delta_translation);
	}
}
}