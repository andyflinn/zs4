
#include "zs4thread.h"
#include "../include/zs4fs.h"

#define BOOST_ALL_NO_LIB
//#define BOOST_SYSTEM_NO_LIB
//#define BOOST_ERROR_CODE_HEADER_ONLY
#define _ALLOW_KEYWORD_MACROS
#define BOOST_EXCEPTION_DISABLE

//#define BOOST_THREAD_NO_LIB

#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/filesystem.hpp>
using namespace std;
using namespace boost::filesystem;


#include <boost/thread/thread.hpp>

bool zs4thread::zs4shutdown = false;

#define DONT_DO_AFTER_SHUTDOWN(x) if (zs4shutdown) return x;
zs4thread::zs4thread(void)
{
	running = false;
	boost::thread launcher(launch, this);
	launcher.detach();
}

zs4thread::~zs4thread(void)
{

}

void zs4thread::launch(zs4thread * t)
{
	t->run();
}

zs4thread::ITERATION_RESULT zs4thread::iterate(void)
{
	return IDLE;
}

bool zs4thread::shutdown(bool initiate)
{
	if (initiate)
		zs4shutdown = true;

	return zs4shutdown;
}

void zs4thread::run(void)
{
	running = true;
	while (!shutdown())
	{
		ITERATION_RESULT result = iterate();
		switch (result){
		case IDLE:
		default:
			running = true;
		}
	}
	running = false;
}

size_t zs4fs::List(const char * name, zs4string * out)
{
	out->clear();

	path p(name);

	if (!exists(p) || !is_directory(p))
		return 0;


	typedef vector<path> vec;             // store paths,
	vec v;                                // so we can sort them later

	copy(directory_iterator(p), directory_iterator(), back_inserter(v));

	sort(v.begin(), v.end());             // sort, since directory iteration
	// is not ordered on some file systems

	size_t count = 0;
	zs4StringBuffer wk;
	for (vec::const_iterator it(v.begin()); it != v.end(); ++it)
	{
		count++;
		out->write((*it).generic_string().c_str());
		out->write("\n");
	}

	return count;
}
