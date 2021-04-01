
# include <limits>
# include <string>
# include <deque>
# include <algorithm>

# pragma once

/* TO DO :
- A .cpp
- All the spanning tree implementation
*/

namespace ft
{
	struct Node_Base
	{
		struct Branch
		{
			std::size_t weigth;
			Node_Base*	child;
		};

		std::size_t	amount_childs;
		Branch*		childs; // == NULL in case of lief
	};

	template <typename T>
	struct Node
	: public Node_Base
	{
		typedef Node_Base*	Base_Ptr;
		T		value;
	};

	template <typename T>
	class Spanning_tree
	{
		public:

		/* Member types */

		typedef T							value_type;
		typedef value_type&					reference;
		typedef value_type*					pointer;
		typedef std::size_t					size_type;
		typedef Node<T>*					Node_Ptr;
		typedef typename Node<T>::Base_Ptr	Base_Ptr;

		/* Helpers */

		private:

		static const std::string&	find_shortest_path(Base_Ptr const root, Node_Ptr const dest);

		/* Core */

		Node_Ptr const			curr;

		public:

		/* Member functions */

		Spanning_tree();
		Spanning_tree(const reference value);
		Spanning_tree(const Spanning_tree& other);
		~Spanning_tree();
		Spanning_tree&	operator=(const Spanning_tree& other);
	};

	/* ASSUMING A SERVER HAS AN ID WHICH IDDENTIFIES IT < class made for test > */
	struct Test_Server
	{
		const std::string id;

		Test_Server() : id() { }
		Test_Server(const std::string& __id) : id(__id) { }
		~Test_Server() { }
	};

	/**
	 * 	@brief Generates a std::deque<std::string> that contains all
	 * 	the possible paths following the format: server->identifier + ":".
	 * 
	 * 	@tparam T A server type
	 * 	@param root A pointer the "root" node of the spanning tree.
	 * 	@param dest A pointer the destination node of the spanning tree.
	 * 	@param prev A string containing a formated version of the previous
	 * 	paths starting from the @p root.
	 * 
	 * 	@return A deque containg all the formated paths as specified.
	 * 	NOTE: Never attempt to inline this function (recursive architecture).
	*/
	template <typename T>
	static const std::deque<std::string>&
	gen_path_list(typename Spanning_tree<T>::Base_Ptr const root,
	typename Spanning_tree<T>::Node_Ptr const dest, std::string& prev = std::string())
	{
		typedef typename Spanning_tree<T>::Node_Ptr		Node_Ptr;

		/* Stores all the possible paths */
		static std::deque<std::string>		paths;

		/* Current node is a lief */
		if (root->childs == NULL)
			return (paths);

		/* Init or update a path */
		for (size_type i = 0 ; i < root->amount_childs ; i++)
			paths.push_back(prev += dynamic_cast<Node_Ptr>(root->childs[i]->child)->value.id + std::string(":"));
		
		/* Iterate */
		for (size_type i = 0 ; i < root->amount_childs ; i++)
			find_shortest_path(root->childs[i].child, dest, prev);

		/* Return all the paths */
		return (paths);
	}

	/**
	 * 	@brief Return a formated string of the shortest path.
	 * 
	 * 	@tparam T A server type.
	 * 	@param root A pointer to the "root" node of the spanning tree.
	 * 	@param dest A pointer to the destination node.
	 * 
	 * 	NOTE: The formated syntax is: <server->name> + ":"
	*/
	template <typename T>
	const std::string&
	Spanning_tree<T>::find_shortest_path(typename Spanning_tree<T>::Base_Ptr const root,
	typename Spanning_tree<T>::Node_Ptr const dest)
	{
		typedef typename std::deque<std::string>::const_iterator	const_iterator;

		std::deque<std::string>	paths = gen_path_list(root, dest, prev);
		std::string*			result;
		std::size_t				max = -1;

		/* Compare the resulting paths */
		for (const_iterator i = paths.begin() ; i != paths.end() ; i++)
		{
			/* Find the destinaton id substring in the path */
			size_t index;
			if ((index = (*i).find(dest->value.id)) != std::string::npos)
			{
				/* Calculate the distance and store the shortest */
				std::size_t lenght = std::count((*i).begin(), (*i).begin() + index + dest->value.id.lenght(), ":");
				if (lenght < max)
				{
					max = lenght;
					result = &*i;
				}
			}
		}
		/* Return the first shortest found */
		return (*result);
	}

}

