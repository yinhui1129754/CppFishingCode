#pragma once
template <class key, class val>
class oMap
{
public:
	oMap();
	~oMap();
	bool set(key, val);
	bool hasKey(key);
	int find(key);
	val  get(key);
	val &operator [] (key);
private:
	vector<key> _key;
	vector<val>_val;
};

template <class key, class val>
oMap<key, val>::oMap()
{

}

template <class key, class val>
oMap<key, val>::~oMap()
{
}
template<class key, class val>
bool oMap<key, val>::set(key k, val v) {
	int num = this->find(k);
	if (num != -1) {
		this->_val[num] = v;
	}
	else {
		this->_key.push_back(k);
		this->_val.push_back(v);
	}
	return true;
};
template <class key, class val>
val  oMap<key, val>::get(key k) {
	int num = this->find(k);
	if (num == -1) {
		return NULL;
	}
	else {
		return this->_val[num];
	}


}
template<class key, class val>
int oMap<key, val>::find(key k) {
	vector<key>::iterator s = std::find(this->_key.begin(), this->_key.end(), k);

	if (s != this->_key.end()) {
		return distance(this->_key.begin(), s);
	}
	else {
		return -1;
	}
};
template<class key, class val>
val&  oMap<key, val>::operator [] (key k) {
	int num = this->find(k);
	if (num == -1) {
		this->_key.push_back(k);
		num = this->find(k);
		this->_val.resize((num + 1));
	}

	return (this->_val[num]);
};
template<class key, class val>
bool oMap<key, val>::hasKey(key k) {
	int num = this->find(k);
	if (num == -1) {
		return false;
	}
	else {
		return true;
	}
}

