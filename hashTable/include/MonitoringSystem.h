
#ifndef MONITORINGSYSTEM_H_INCLUDED
#define MONITORINGSYSTEM_H_INCLUDED

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include<iostream>
using namespace std;
//this monitoringSystem class is hash table
// we made a little modification to this class(we added some function)

int nextPrime(int n);



// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTable
{
public:
    explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
    {
        makeEmpty( );
    }

    bool contains( const HashedObj & x )
    {
        return isActive( findPos( x ) );
    }

    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : array )
            entry.info = EMPTY;
    }


    bool insert( const HashedObj & x )
    {

        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ].element = x;
        array[ currentPos ].info = ACTIVE;

        // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }



    bool insert( HashedObj && x )
    {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ] = std::move( x );
        array[ currentPos ].info = ACTIVE;

        // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        return true;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

    //MODIFIED


    HashedObj getX(int i)// it returns the element inside the object in the array cell
    {
        if (i<array.size())
        {
            return array[i].element;
        }

    }
    int findPos( const HashedObj & x )// we made findPos a public function so we can use it later
    {
        int offset = 1;
        int currentPos = myhash( x );

        while( array[ currentPos ].info != EMPTY &&
                array[ currentPos ].element != x )
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }

        return currentPos;
    }

    void print()
    {
        int numOfElement = currentSize;
        for(int i=0; i<array.size()&& numOfElement>0; i++)
        {
            if(array[i].info == ACTIVE)
            {
                cout<<array[i].element;
                numOfElement--;
            }
        }
    }

private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
            : element{ e }, info{ i } { }

        HashEntry( HashedObj && e, EntryType i = EMPTY )
            : element{ std::move( e ) }, info{ i } { }
    };

    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const
    {
        return array[ currentPos ].info == ACTIVE;
    }



    void rehash( )
    {
        vector<HashEntry> oldArray = array;

        // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( auto & entry : array )
            entry.info = EMPTY;

        // Copy table over
        currentSize = 0;
        for( auto & entry : oldArray )
            if( entry.info == ACTIVE )
                insert( std::move( entry.element ) );
    }

    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % array.size( );
    }
};



#endif // MONITORINGSYSTEM_H_INCLUDED
