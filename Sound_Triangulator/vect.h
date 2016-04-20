struct Vect
{
    float x;  //X pos
    float y;  //Y pos

    //Add vectors
    Vect operator +(const Vect& other)
    {
        Vect ret = {x + other.x, y + other.y};
        return ret;
    }

    //Add assign vectors
    Vect operator +=(const Vect& other)
    {
        x += other.x;
        y += other.y;
    }

    //Multiply this by a constant.
    Vect operator *(const float& other)
    {
        Vect ret = {x * other, y * other};
        return ret;
    }

    //Get the dot product between this and another vector.
    float getDot(Vect other)
    {
        return x * other.x + y * other.y;
    }

    //Return the length of this vector
    float getLength()
    {
        return sqrt(x * x + y * y);
    }

    //Get the unsigned angle between this vector and another.
    float getAngleBetween(Vect other)
    {
        return acos(getDot(other) / (getLength() * other.getLength()));
    }
};

