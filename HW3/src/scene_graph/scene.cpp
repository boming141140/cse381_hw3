// IN THIS FILE WE'LL BE DECLARING METHODS DECLARED INSIDE THIS HEADER FILE
#include "scene.hpp"

// OUR OWN TYPES
#include "component.hpp"
#include "node.hpp"

namespace W3D::sg
{
Scene::Scene(const std::string &name) :
    name_(name)
{
}

void Scene::add_node(std::unique_ptr<Node> &&pNode)
{
	p_nodes_.emplace_back(std::move(pNode));
}

void Scene::add_child(Node &child)
{
	root_->add_child(child);
}

std::unique_ptr<sg::Node> Scene::release_root_node()
{
	// Find the root node in the vector of nodes and remove it, returning ownership to the caller.
	for (auto iter = p_nodes_.begin(); iter != p_nodes_.end(); ++iter)
	{
		if (iter->get() == root_)
		{
			std::unique_ptr<sg::Node> root_node = std::move(*iter);
			p_nodes_.erase(iter);
			root_ = nullptr;         // Clear the root pointer as it is no longer part of this scene.
			return root_node;        // Return the unique_ptr, transferring ownership.
		}
	}
	return nullptr;        // In case the root node was not found.
}

void Scene::add_component(std::unique_ptr<Component> &&pComponent)
{
	if (pComponent)
	{
		p_components_[pComponent->get_type()].push_back(std::move(pComponent));
	}
}

void Scene::add_component_to_node(std::unique_ptr<Component> &&pComponent, Node &node)
{
	if (pComponent)
	{
		node.set_component(*pComponent);
		p_components_[pComponent->get_type()].push_back(std::move(pComponent));
	}
}

void Scene::set_components(const std::type_index                   type,
                           std::vector<std::unique_ptr<Component>> pComponents)
{
	p_components_[type] = std::move(pComponents);
}

void Scene::set_root_node(Node &node)
{
	root_ = &node;
}

void Scene::set_nodes(std::vector<std::unique_ptr<Node>> &&nodes)
{
	p_nodes_ = std::move(nodes);
}

Node &Scene::get_root_node()
{
	return *root_;
}

Node *Scene::find_node(const std::string &name)
{
	for (auto &pNode : p_nodes_)
	{
		if (pNode->get_name() == name)
		{
			return pNode.get();
		}
	}

	return nullptr;
}

const std::vector<std::unique_ptr<Component>> &Scene::get_components(
    const std::type_index &type) const
{
	return p_components_.at(type);
}

bool Scene::has_component(const std::type_index &type) const
{
	return p_components_.count(type) > 0;
}
}        // namespace W3D::sg