#include <memory>

namespace ft
{
	template <class T, class Alloc = std::allocator<T>>
	class vector
	{
	public:
		typedef T        value_type;
		typedef Alloc    allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		iterator?
		const_iterator?
		reverse_iterator?
		const_reverse_iterator?

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
				: _head(null_ptr), _size(0), _alloc(alloc), _capacity(0);

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
				alloc.destroy(&_head[i]);
			_alloc.deallocate(_head, _capacity);
		}
		//Оператор присваивания. копирует все элементы из Х в контейнер
		vector& operator=(const vector& x)
		{
			vector copy(x);
			swap(copy);
			return (*this);
		}

		// Капасити

		size_type size() const {return _size;}

		//Потенциально максимально возможный размер, который может хранить контейнер. Зависит от ограничений системы или
		//реализации. Аллоцирование такого объема памяти не гарантированно, мы просто обещаем попытаться.
		size_type max_size() {return _alloc.max_size();} 

		resize????

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





	};
}