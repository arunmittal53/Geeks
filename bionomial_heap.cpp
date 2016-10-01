// arunmittal53
#include<bits/stdc++.h>
using namespace std;
struct node{
	int data;
	int degree;
	node *child;
	node *sibling;
	node *parent;
};
node* newNode(int key)
{
	node *temp = (node*)malloc(sizeof(node));
	temp->data = key;
	temp->degree = 0;
	temp->child = temp->parent = temp->sibling = NULL;
	return temp;
}

node* merge_btree(node *head, node *temp)
{
	if(head->data > temp->data)
		swap(head,temp);
	temp->parent = head;
	temp->sibling = head->child;
	head->child = temp;
	head->degree++;
	return head;
}

list<node*> union_bionomial_heap(list<node*> l1, list<node*> l2)
{
	list<node*> _new;
	list<node*>::iterator it,ot;
	it = l1.begin();
	ot = l2.begin();
	while(it!=l1.end() && ot!=l2.end())
	{
		if((*it)->degree <= (*ot)->degree)
		{
			_new.push_back(*it);
			it++;
		}
		else
		{
			_new.push_back(*ot);
			ot++;
		}
	}
	while(it!=l1.end())
	{
		_new.push_back(*it);
		it++;
	}
	while(ot!=l2.end())
	{
		_new.push_back(*ot);
		ot++;
	}
	return _new;
}

list<node*> adjust(list<node*> _heap)
{
	if(_heap.size() <= 1)
		return _heap;
	list<node*> new_heap;
	list<node*>::iterator it1,it2,it3;
	it1=it2=it3 = _heap.begin();
	if(_heap.size() == 2)
	{
		it2 = it1;	it2++;
		it3 = _heap.end();
	}
	else
	{
		it2++;	it3=it2;	it3++;
	}
	while(it1 != _heap.end())
	{
		if(it2 == _heap.end())
			it1++;
		else if((*it1)->degree < (*it2)->degree)
		{
			it1++;	it2++;
			if(it3!=_heap.end())
				it3++;
		}
		else if(it3!=_heap.end() && (*it1)->degree == (*it2)->degree && (*it1)->degree == (*it3)->degree)
		{
			it1++;	it2++;	it3++;
		}
		else if((*it1)->degree == (*it2)->degree)
		{
			node *temp;
			*it1 = merge_btree(*it1,*it2);
			it2 = _heap.erase(it2);
			if(it3 != _heap.end())
				it3++;
		}
	}
	return _heap;
}

list<node*> insert_a_tree_in_heap(list<node*> _heap,node *tree)
{
		list<node*> temp;
		temp.push_back(tree);
		temp = union_bionomial_heap(_heap,temp);
		return adjust(temp);
}
list<node*> insert_a_key_in_heap(list<node*> _head,int key)
{
	node *temp;
	temp = newNode(key);
	return insert_a_tree_in_heap(_head,temp);
}

void print_tree(node *h)
{
	while(h)
	{
		cout<<h->data<<" ";
		print_tree(h->child);
		h = h->sibling;
	}
}

void print_heap(list<node*> _heap)
{
	list<node*> ::iterator it;
	it = _heap.begin();
	while(it != _heap.end())
	{
		print_tree(*it);
		cout<<"\n";
		it++;
	}
}

node* get_min(list<node*> _heap)
{
	node *temp;
	list<node*>::iterator it;
	it = _heap.begin();
	temp = *it;
	while(it != _heap.end())
	{
		if((*it)->data < temp->data)
		{
			temp = *it;
		}
		it++;
	}
	return temp;
}

list<node*> remove_min_from_tree_return_bheap(node *tree)
{
	list<node*> heap;
	node *temp = tree->child;
	node *lo;
	while(temp)
	{
		lo = temp;
	    temp = temp->sibling;
		lo->sibling = NULL;
		heap.push_front(lo);
	}
	return heap;
}

list<node*> extract_min(list<node*> _heap)
{
	list<node*> new_heap,lo;
	node *temp;
	temp = get_min(_heap);
    list<node*>::iterator it;
	it = _heap.begin();
	while(it != _heap.end())
	{
		if(*it != temp)
		{
			new_heap.push_back(*it);
		}
		it++;
	}
	lo = remove_min_from_tree_return_bheap(temp);
	new_heap = union_bionomial_heap(new_heap,lo);
	new_heap = adjust(new_heap);
	return new_heap;
}

int main()
{
	int ch,key;
	list<node*> _heap;
	while(1)
	{
		cout<<"enter 0 to break, 1 to insert element, 2 to print min,3 to extract min and print heap, 4 to print heap\n";
		cin>>ch;
		if(ch == 0)
			break;
		else if(ch == 1)
		{
			cout<<"enter key to be inserted\n";
			cin>>key;
			_heap = insert_a_key_in_heap(_heap,key);
		}
		else if(ch == 2)
		{
			node *temp;
			temp = get_min(_heap);
			cout<<temp->data<<"\n";
		}
		else if(ch == 3)
		{
			_heap = extract_min(_heap);
			print_heap(_heap);
		}
		else if(ch == 4)
		{
			print_heap(_heap);
		}
		else
			cout<<"Invalid choice\n";
				
	}
	return 0;
}
