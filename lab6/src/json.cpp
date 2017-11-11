#include "include/json.h"

std::string ToString(int a) {
	std::ostringstream ss;
	ss << a;
	return ss.str();
}

void GraphBintree(tree *tr) {
	JsonBox::Object obj;
	int i = 0;

	if (tr != NULL) {
		GraphBintreeRecure(tr, obj, i, 0, 0, 250, 20);
	}

	JsonBox::Value json(obj);
	json.writeToFile("tree.json");
}

void GraphBintreeRecure(tree *tr, JsonBox::Object &obj, int &i, int x, int y, int size_x, int size_y) {
	std::string value = "n";
	value += ToString(i);
	obj["nodes"][i]["id"] = JsonBox::Value(value);
	value = ToString(tr->data);
	obj["nodes"][i]["label"] = JsonBox::Value(value);
	obj["nodes"][i]["x"] = JsonBox::Value(x);
	obj["nodes"][i]["y"] = JsonBox::Value(y);
	obj["nodes"][i]["size"] = JsonBox::Value(size_x+30);
	int line = i;
	if(tr->l != NULL) {
		value = "e";
		value += ToString(i);
		obj["edges"][i]["id"] = JsonBox::Value(value);
		value = "n";
		value += ToString(line);
		obj["edges"][i]["source"] = JsonBox::Value(value);
		i++;
		value = "n";
		value += ToString(i);
		obj["edges"][i-1]["target"] = JsonBox::Value(value);
		GraphBintreeRecure(tr->l, obj, i, x-size_x, y+size_y, size_x/2, size_y-2);
	}
	if(tr->r != NULL) {
		value = "e";
		value += ToString(i);
		obj["edges"][i]["id"] = JsonBox::Value(value);
		value = "n";
		value += ToString(line);
		obj["edges"][i]["source"] = JsonBox::Value(value);
		i++;
		value = "n";
		value += ToString(i);
		obj["edges"][i-1]["target"] = JsonBox::Value(value);
		GraphBintreeRecure(tr->r, obj, i, x+size_x, y+size_y, size_x/2, size_y-2);
	}
}