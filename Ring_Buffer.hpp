
/*
	Creator : Emre iris
	Date    : 07/09/2021
	Version : 1.0
	Brief   : Ring buffer implementation for general purpose usage.
*/

#pragma once

template<class type>
class Ring_Buffer
{
public:
	Ring_Buffer(size_t _size): size(_size) 
	{
		base_pointer = new type[size];

		if (base_pointer == nullptr)
			return;
	}

	~Ring_Buffer()
	{
		delete[] base_pointer;
	}

	size_t get_capacity() { return size; }

	size_t get_size()
	{
		size_t _size = size;

		if (!full)
		{
			if (head >= tail)
			{
				_size = head - tail;
			}
			else
			{
				_size = size + (head - tail);
			}
		}

		return _size;
	}

	void add_data(type data) 
	{
		base_pointer[head] = data;

		if (is_full())
		{
			tail = (tail + 1) % size;
		}

		head = (head + 1) % size;

		full = head == tail;

	}

	type get_data()
	{
		if (is_empty())
			return type();

		auto temp = base_pointer[tail];

		tail = (tail + 1) % size;
		full = false;

		return temp;
	}
private:
	bool is_full() const
	{
		return full;
	}

	bool is_empty() const
	{
		return (!full) && (head == tail);
	}


private:
	type* base_pointer = nullptr;
	size_t size = 0;
	size_t head = 0;
	size_t tail = 0;
	bool full = false;
};
