//=========
// map.hpp
//=========

// Implementation of a sorted map
// Items can be inserted, removed and looked-up in constant low time

// Copyright 2024, Sven Bieg (svenbieg@web.de)
// http://github.com/svenbieg/Clusters


#pragma once


//=======
// Using
//=======

#include "index.hpp"


//===========
// Namespace
//===========

namespace Collections {


//======================
// Forward-Declarations
//======================

template <typename _key_t, typename _value_t, typename _size_t, uint16_t _group_size> class map;
template <typename _key_t, typename _value_t> class map_item;
template <typename _traits_t, bool _is_const> class shared_map_iterator;

template <typename _key_t, typename _value_t, typename _size_t, uint16_t _group_size>
struct map_traits
{
using key_t=_key_t;
using item_t=map_item<_key_t, _value_t>;
using group_t=index_group<_key_t, item_t, _size_t, _group_size>;
using item_group_t=index_item_group<_key_t, item_t, _size_t, _group_size>;
using parent_group_t=index_parent_group<_key_t, item_t, _size_t, _group_size>;
using cluster_t=map<_key_t, _value_t, _size_t, _group_size>;
using iterator_t=index_iterator<map_traits, false>;
using const_iterator_t=index_iterator<map_traits, true>;
using shared_iterator_t=shared_map_iterator<map_traits, false>;
using shared_const_iterator_t=shared_map_iterator<map_traits, true>;
using size_t=_size_t;
static constexpr uint16_t group_size=_group_size;
};


//======
// Item
//======

template <typename _key_t, typename _value_t>
class map_item
{
public:
	// Con-/Destructors
	map_item(map_item const& item): m_key(item.m_key), m_value(item.m_value) {}
	map_item(map_item&& item): m_key(std::move(item.m_key)), m_value(std::move(item.m_value)) {}
	map_item(_key_t const& key, _value_t const& value): m_key(key), m_value(value) {}

	// Assignment
	inline map_item& operator=(map_item const& item)
		{
		m_key=item.m_key;
		m_value=item.m_value;
		return *this;
		}

	// Comparison
	inline bool operator==(_key_t const& key)const { return m_key==key; }
	inline bool operator!=(_key_t const& key)const { return m_key!=key; }
	inline bool operator>(_key_t const& key)const { return m_key>key; }
	inline bool operator>=(_key_t const& key)const { return m_key>=key; }
	inline bool operator<(_key_t const& key)const { return m_key<key; }
	inline bool operator<=(_key_t const& key)const { return m_key<=key; }

	// Access
	inline _key_t const& get_key()const { return m_key; }
	inline _value_t& get_value() { return m_value; }
	inline _value_t const& get_value()const { return m_value; }

	// Modification
	inline void set_value(_value_t const& value) { m_value=value; }

private:
	// Common
	_key_t m_key;
	_value_t m_value;
};


//=====
// Map
//=====

template <typename _key_t, typename _value_t, typename _size_t=uint32_t, uint16_t _group_size=10>
class map: public cluster<map_traits<_key_t, _value_t, _size_t, _group_size>>
{
public:
	// Using
	using _traits_t=map_traits<_key_t, _value_t, _size_t, _group_size>;
	using _base_t=cluster<_traits_t>;
	using _item_t=typename _traits_t::item_t;
	using _group_t=typename _traits_t::group_t;
	using _item_group_t=typename _traits_t::item_group_t;
	using _parent_group_t=typename _traits_t::parent_group_t;
	using iterator=typename _traits_t::iterator_t;
	using const_iterator=typename _traits_t::const_iterator_t;

	// Con-/Destructors
	map(): _base_t(nullptr) {}
	map(map&& map): _base_t(map.m_root)
		{
		map.m_root=nullptr;
		}
	map(map const& map): _base_t(nullptr)
		{
		copy_from(map);
		}

	// Access
	template <class _key_param_t> inline _value_t& operator[](_key_param_t&& key) { return get(std::forward<_key_param_t>(key)); }
	inline const_iterator cfind(_key_t const& key, find_func func=find_func::equal)const
		{
		const_iterator it(this);
		it.find(key, func);
		return it;
		}
	bool contains(_key_t const& key)const
		{
		auto root=this->m_root;
		if(!root)
			return false;
		return root->get(key)!=nullptr;
		}
	inline iterator find(_key_t const& key, find_func func=find_func::equal)
		{
		iterator it(this);
		it.find(key, func);
		return it;
		}
	_value_t& get(_key_t const& key)
		{
		_item_t create(key, _value_t());
		bool created=false;
		_item_t* got=get_internal(std::forward<_item_t>(create), &created);
		return got->get_value();
		}
	_value_t& get(_key_t const& key, _value_t const& value)
		{
		_item_t create(key, value);
		bool created=false;
		_item_t* got=get_internal(std::forward<_item_t>(create), &created);
		return got->get_value();
		}
	_value_t const& get(_key_t const& key)const
		{
		auto root=this->m_root;
		if(!root)
			throw std::out_of_range(nullptr);
		_item_t* item=root->get(key);
		if(!item)
			throw std::out_of_range(nullptr);
		return item->get_value();
		}
	bool try_get(_key_t const& key, _value_t* value)const
		{
		auto root=this->m_root;
		if(!root)
			return false;
		_item_t* item=root->get(key);
		if(!item)
			return false;
		*value=item->get_value();
		return true;
		}

	// Modification
	map& operator=(map&& map)
		{
		this->clear();
		this->m_root=map.m_root;
		map.m_root=nullptr;
		return *this;
		}
	inline map& operator=(map const& map)
		{
		this->copy_from(map);
		return *this;
		}
	bool add(_key_t const& key, _value_t const& value)
		{
		_item_t create(key, value);
		bool created=false;
		get_internal(create, &created);
		return created;
		}
	bool remove(_key_t const& key, _item_t* item_ptr=nullptr)
		{
		auto root=this->m_root;
		if(!root)
			return false;
		return root->remove(key, item_ptr);
		}
	bool set(_key_t const& key, _value_t const& value)
		{
		_item_t create(key, value);
		bool created=false;
		auto got=get_internal(create, &created);
		if(!created)
			got->set_value(value);
		return true;
		}

protected:
	// Con-/Destructors
	map(_group_t* root): _base_t(root) {}

private:
	// Common
	_item_t* get_internal(_item_t const& create, bool* created)
		{
		auto root=this->create_root();
		_item_t* got=root->get(create.get_key(), create, created, false);
		if(got)
			return got;
		root=this->lift_root();
		return root->get(create.get_key(), create, created, true);
		}
};

}