namespace jly_tutorials
{
	void main_union()
	{
        union
        {
            float m[3];

            struct
            {
                float x, y, z;
            };
        } u;
        u.x = 1.0f;
        u.m[0] = 2.0f;
	}
}