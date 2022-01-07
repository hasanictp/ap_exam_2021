#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <stdlib.h>


using namespace std;
template<typename T, typename N=size_t>
class list_pool{
    public:
    
       typedef T value_type;
       typedef N list_type;
       
 
    struct node_t{
        value_type value;
        list_type next;
    };
    vector<node_t> pool;

  //  using list_type = N;
   // using value_type = T;
   
    using size_type = typename vector<node_t>::size_type;

    list_type free_node_list=end();
    list_type index=1;

    node_t& node(list_type x) 
    { 
    	return pool[x-1]; 
    }
    const node_t& node(list_type x) const  
    { 
    return pool[x-1]; 
    }

    public:

    list_pool()=default;

    explicit list_pool(size_type n)
    {   
        pool.reserve(n);
    }

 //****************************************************
    list_type push_front(value_type&& val, list_type head){
         if(free_node_list==0)
         { 
            value(index)=forward<value_type>(val);
            return index;
        }
        else
        {
        auto  temp = free_node_list;
        free_node_list=next(free_node_list);
        value(temp)=forward<value_type>(val);     
        next(temp)=head;     
        return temp;
            
        }
    }

//******************************************************************
    list_type push_back(value_type&& val, list_type head)
    {
       list_type temp{head};
        if(head == 0)
        {   
        
        value(index)=val;
        return index;
        
        }
        while(next(temp)!=0)
        {
            temp=next(temp);
        }
        if(free_node_list==0)
        {
         
         index++;
         next(temp)=index;
         value(index)=forward<value_type>(val);
         next(index)=end();
         
         return head;
        }
        else
        {
            return head;
        }
    }

//**********************************************************

    T& value(list_type x)
    {
    	return node(x).value;
    }

    list_type& next(list_type x)
    {
     	return node(x).next;
    }

    list_type end() const  
    { 
        return 0; 
    }

    list_type new_list()
    { 
    	return end(); 
    }

    bool is_empty(list_type x) const
    {
      return x==end();
    }
    
//**************************************************************
    list_type free(list_type x) 
    {
        if(x!=end())
        {
        	auto temp=node(x).next;
                return temp;
        	
	}
	else
	{
       		return x;
    	}
    }
    
  list_type free_list(list_type temp)
  {
	if(free_node_list)
	{
		 while (node(temp).next)	
   	   	{
   			temp = node(temp).next;
	   	}
   
    	return temp;
	}
	else
	{
		free_node_list=temp;
	}
	
        return end();
  } 
  
    
};


