struct Vect
{
    float x;
    float y;
    
    Vect operator +(const Vect& other)
    {
        Vect ret = {x + other.x, y + other.y};
        return ret;
    }
    
    Vect operator -(const Vect& other)
    {
        Vect ret = {x - other.x, y - other.y};
        return ret;
    }
};

