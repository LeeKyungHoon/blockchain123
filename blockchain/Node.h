

template<typename T>
class Node {
private:
	T data;
	Node* parent;
	Node* sibling;

public:
	Node(T data) { this->data = data; parent = nullptr; sibling = nullptr; };
	~Node() { DeleteNode(parent);DeleteNode(sibling) };
	void DeleteNode(Node* n) {	if (n == nullptr)return; delete n;};
	void setData() { this->data = data; };
	void setParent(Node* parent) { this->parent = parent; };
	void setSibling(Node* sibling) {this->sibling = sibling};
	T GetData() {return data};
	Node* GetParent() {return parent};
	Node* GetSibling() {return sibling};

};