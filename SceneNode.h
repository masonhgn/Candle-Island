#include <SFML/Graphics.hpp>
#include <memory>
#include <assert.h>
class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
	typedef std::unique_ptr<SceneNode> Ptr;
public:
	SceneNode();
	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	std::vector<Ptr> children;
	SceneNode* parent;
};

SceneNode::SceneNode() {

}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	drawCurrent(target, states);
	for (auto i = children.begin(); i != children.end(); ++i) (*i)->draw(target, states);
}

void SceneNode::attachChild(Ptr child) {
	child->parent = this; //takes ownership of this child by setting the child's parent to itself
	children.push_back(std::move(child)); //adds child to the children vector
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) {
	auto found = std::find_if(children.begin(), children.end(), [&](Ptr& p) -> bool { return p.get() == &node; });
	assert(found != children.end()); //debug function
	Ptr result = std::move(*found); //we move the node into result
	result->parent = nullptr; 
	children.erase(found); //erase empty element from container
	return result;
}




