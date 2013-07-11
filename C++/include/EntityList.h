#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include <Entity.h>
#include <VectorIterator.h>

class EntityList : public Entity
{
private:
	
	vector<Entity*> entities;
	
public:

	EntityList();
	
	EntityList( const size_t entityTypeId );

	EntityList( EntityType *type );

	void add( Entity *e );

	void add( initializer_list<Entity*> e );
	
	template<typename Iterator>
	void add( Iterator first, Iterator end )
	{
		for (Iterator i = first; i != end; i++)
		{
			add(i);
		}
	}

	void add( const vector<Entity*> &e );

	void clean();

	void draw( void *drawState );

	void update( void *updateState );


   	typedef bool (*EntityFilter)(const Entity *e);

	struct FilterFunctor
	{
		virtual bool operator()( Entity *e );
	};


	VectorIteratorPointer<Entity*, EntityFilter> begin();

	VectorIteratorPointer<Entity*, EntityFilter> end();

	template<typename F>
	inline VectorIterator<Entity*, F> filter(F filterFunction)
	{
		return VectorIterator<Entity*, F>(&entities, filterFunction);
	}

 	VectorIterator<Entity*, FilterFunctor> filterByComponents(initializer_list<size_t> componentIds);

	VectorIterator<Entity*, FilterFunctor> filterByControllers(initializer_list<size_t> controllerIds);

	VectorIterator<Entity*, FilterFunctor> filterByValue(const size_t componentId, const AnyMemory &value);

	VectorIterator<Entity*, FilterFunctor> filterByVisible(bool visible);

	VectorIterator<Entity*, FilterFunctor> filterByEnabled(bool enabled);

	vector<Entity*>& getEntities()
	{
		return entities;
	}

	inline size_t getSize()
	{
		return entities.size();
	}

	inline Entity* operator[](const size_t index)
	{
		return ( index < entities.size() ? entities.at(index) : NULL );
	}

	inline EntityList& operator+=(Entity *e)
	{
		add( e );
		return *this;
	}

	inline EntityList& operator<<(Entity *e)
	{
		add( e );
		return *this;
	}

protected:

	virtual void onEntityAdd( Entity *e, const size_t index ) {}

	virtual void onEntityRemove( Entity *e, const size_t index ) {}

	virtual void onEntityUpdated( Entity *e, void *updateState ) {}

private:

	void internalAdd( Entity *e );

};


#endif