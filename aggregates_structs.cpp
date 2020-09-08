/*
* https://www.nextptr.com/tutorial/ta1244731691/can-emplace_back-replace-push_back
Aggregates and Brace-Initialization
An aggregate (usually, a plain old struct) can be brace-initialized and inserted using push_back:

struct Point { int x,y; };

std::vector<Point> points;
//insert with brace-initialization
points.push_back({10,20});
Unfortunately, as of now, there is no-way to brace-initialize an aggregate using emplace. Unlike the previous one, this point could be simply a matter of a little inconvenience, but only if you know that it is merely a superficial matter. Until then, it could be very confounding.

Quite reasonably, using emplace_back to brace-initialize and insert fails to compile because the brace-list cannot resolve to the struct:

points.emplace_back({10,20}); //ERROR
What is more vexing is that the standard emplace also does not work because the struct does not have a required constructor defined:

points.emplace_back(10,20); //ERROR
We must define a constructor for the struct, or turn it into a non-aggregate, to make it emplace-able:

struct Point {
 Point(int x_,int y_):x(x_),y(y_){}
 int x,y;
};

//good now
points.emplace_back(10,20);

*/