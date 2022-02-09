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

		//copy constructor. Создает контейнер с копиями каждого элемента x
		vector(const vector& x) : _size(x._size), _capacity(x._capacity),
								 _alloc(x._alloc)
		{
			_head = _alloc.allocate(_capacity);
			size_type i = 0;
			while (i < _size)
				_alloc.construct(&_head[i], x._head[i]);
		}

		//деструктор
		~vector()
		{
			for (iterator it = begin(); it != end(); ++it)
				_alloc.destroy(&(*it));
			_alloc.deallocate(_vector, _capacity);
		}
	};
}