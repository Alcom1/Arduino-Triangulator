struct Vect
{
    float x;
    float y;
    
    Vect operator +(const Vect& other)
    {
        Vect ret = {x + other.x, y + other.y};
        return ret;
    }
    
    Vect operator +=(const Vect& other)
    {
        x += other.x;
        y += other.y;
    }
    
    Vect operator *(const float& other)
    {
        Vect ret = {x * other, y * other};
        return ret;
    }
    
    float getLength()
    {
        return sqrt(x * x + y * y);
    }

    float getAngleBetween(Vect other)
    {
        return acos(getDot(other) / (getLength() * other.getLength()));
    }

    float getDot(Vect other)
    {
        return x * other.x + y * other.y;
    }
};

