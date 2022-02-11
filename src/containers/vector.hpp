#include <memory>
#include <stdexcept>
#include <cstddef>
#include "./utils/iterators.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T        value_type;
		typedef Alloc    allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef vector_iterator<T>							iterator;
		typedef vector_iterator<const T>					const_iterator;
		//TO DO: reverse iterator

		typedef ptrdiff_t 	difference_type;
		typedef size_t 		size_type;

	private:
		size_type       _size;
		size_type       _capacity;
		pointer         _head;
		Alloc           _alloc;

	public:
		//дефолтный конструктор. Создает пустой контейнер без элементов
		explicit vector (const allocator_type& alloc = allocator_type())
				: _head(NULL), _size(0), _alloc(alloc), _capacity(0) {};

		//fill constructor. Создает контейнер из n элементов. Каждый элемент это копия val
		explicit vector (size_type n, const value_type& val = value_type(),
				   const allocator_type& alloc = allocator_type())
				   : _alloc(alloc), _size(n), _capacity(n)
		{
			_head = _alloc.allocate(_capacity);
			size_type i = 0;
			while (i++ < _size)
				_alloc.construct(&_head[i], val);
		}

		//range constructor. Создает [first, last] элементов. Значение
		// каждого элемента равно тому же, что и в [first, last]
		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type()) :
				_alloc(alloc), _capacity(0), _size(0)
		{
			this->assign (first, last);
		}

		//copy constructor. Создает контейнер с копиями каждого элемента Х
		vector(const vector& x) : _size(x._size), _capacity(x._capacity),
								  _alloc(x._alloc)
		{
			_head = _alloc.allocate(_capacity);
			size_type i = 0;
			while (i++ < _size)
				_alloc.construct(&_head[i], x._head[i]);
		}

		//деструктор
		~vector()
		{
			size_type i = 0;
			while (i++ < _size)
				_alloc.destroy(&_head[i]);
			_alloc.deallocate(_head, _capacity);
		}
		//Оператор присваивания. копирует все элементы из Х в контейнер
		vector& operator=(const vector& x)
		{
			vector copy(x);
			swap(copy);
			return (*this);
		}

		// Капасити_____________________________________________________

		size_type size() const {return _size;}

		//Потенциально максимально возможный размер, который может хранить контейнер. Зависит от ограничений системы или
		//реализации. Аллоцирование такого объема памяти не гарантированно, мы просто обещаем попытаться.
		size_type max_size() {return _alloc.max_size();}

		//TODO: resize function

		size_type capacity() const {return _capacity;}

		//Проверка пустой ли контейнер или нет?
		bool empty() const {return _size == 0;}

		//Запрос на изменение капасити. Если запрашивается капасити больше, чем есть сейчас, то происходит реаллокация
		//во всех остальных случаях не происходит ничего

		void reserve(size_type n)
		{
			if (n > this->max_size())
				throw std::length_error("resized above max_size");
			if (n > _capacity)
				reallocate(n);
		}

		//Элемент аксесс_________________________________________________
		reference operator[] (size_type n) {return _head[n];} // вызвать
		// эту функцию с n вне границ контейнера - УБ
		const_reference operator[] (size_type n) const {return _head[n];}

		//тоже самое, но бросает эксепшн в случае, если n находится вне
		// границ контейнера
		reference at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("out-of-range");
			return (_head[n]);
		}

		const_reference at(size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("out-of-range");
			return (_head[n]);
		}

		//модиферс___________________________________________-

		reference front() {return _head[0];}
		const_reference front() const {return _head[0];}
		reference back() {return _head[_size - 1];}
		const_reference back() const {return _head[_size - 1];}

		//assign range - элементы контейнера создаются из диапазона [first, last]
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)
		{
			// сначала ищем n, затем создаем контейнер с нужным количеством памяти, чтобы при каждом push_back по
			// новой не аллоцировать память и не копировать туда данные
			difference_type n = 0;
			InputIterator count(first);
			while (count != last)
			{
				++count;
				++n;
			}
			this->clear();
			this->reserve(n);
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}

		//assign fill - создает n элементов со значением val
		void assign(size_type n, const value_type& val)
		{
			this->clear();
			this->reserve(n);
			size_type i = 0;
			while (i++ < n)
				this->push_back(val);
		}

		void push_back(const value_type& val)
		{
			if (_size >=_capacity)
				reallocate(capacity_extension(_size + 1));
			_alloc.construct(&_head[_size++], val);
		}

		void pop_back() { _alloc.destroy(&_head[--_size]);}

		//single element insert - Вставляем элемент перед элементом на указанной позиции. Реаллокация должна
		// происходить только в том случае, если новый размер контейнера превышает капасити.
		iterator insert(iterator position, const value_type& val)
		{
			if (_size + 1 > _capacity)
				reallocate(capacity_extension(_size + 1));
			difference_type shift = (position - this->begin());
			if (_size + 1 > _capacity)
				reallocate(capacity_extension(_size + 1));
			this->insert(iterator(this->begin() + shift), 1, val);
			return (iterator(this->begin() + shift));
		}

		// fill insert - тоже самое что и single insert, но вставляем не один, а n элементов
		void insert(iterator position, size_type n, const value_type& val)
		{
			if (n == 0)
				return;
			if (_size + n > _capacity)
				reallocate(capacity_extension(_size + n));
			difference_type shift = position - this->begin();
			difference_type tmp = this->end() - this->begin();

			this->resize(this->_size + n);
			iterator end = this->end();
			position = this->begin() + shift;
			iterator tmp_end = this->begin() + tmp;
			while (tmp_end != position)
			{
				--end;
				--tmp_end;
				*end = *tmp_end;
			}
			while (n--)
				*position++ = val;
		}

		void clear()
		{
			size_type i = 0;
			while (i++ < _size)
				_alloc.destroy(&_head[i]);
			_size = 0;
		}



	private:
		size_type capacity_extension(size_type new_size)
		{
			size_type		multiplier = 2;

			size_type	new_capacity = (_capacity > 0 ? _capacity : 1);
			while (new_capacity < new_size)
				new_capacity *= multiplier;
			return (new_capacity);
		}

		void reallocate(size_type new_capacity)
		{
			pointer new_vector = _alloc.allocate(new_capacity);
			size_type i = 0;
			while (i++ < _size)
			{
				_alloc.construct(&new_vector[i], _head[i]);
				_alloc.destroy(&_head[i]);
			}
			if (_capacity)
				_alloc.deallocate(_head, _capacity);
			_head = new_vector;
			_capacity = new_capacity;
		}

	};
}