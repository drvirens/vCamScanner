//
//  city_geo.cpp
//  HelloCpp
//
//  Created by Virendra Shakya on 11/20/13.
//
//

#if 0

#include "city_geo.h"


  //viren+

  // to run, you must download and extract cities.txt from:
  // http://geolite.maxmind.com/download/worldcities/cities.txt.gz
#include "VpTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdint.h>
#include <string>
#include <string.h>
#include <math.h>

#define DIM 200
#define NUM 32000

void QueryPerformanceCounter( uint64_t* val )
{
  timeval tv;
  struct timezone tz = {0, 0};
  gettimeofday( &tv, &tz );
  *val = tv.tv_sec * 1000000 + tv.tv_usec;
}

struct VirenMyPoint {
  std::string city;
  double latitude;
  double longitude;
};

double distance( const VirenMyPoint& p1, const VirenMyPoint& p2 )
{
  double a = (p1.latitude-p2.latitude);
  double b = (p1.longitude-p2.longitude);
  return sqrt(a*a+b*b);
}

struct HeapItem {
  HeapItem( int index, double dist) :
  index(index), dist(dist) {}
  int index;
  double dist;
  bool operator<( const HeapItem& o ) const {
    return dist < o.dist;
  }
};

void linear_search( const std::vector<VirenMyPoint>& items, const VirenMyPoint& target, int k, std::vector<VirenMyPoint>* results,
                   std::vector<double>* distances)
{
  std::priority_queue<HeapItem> heap;
  for ( int i = 0; i < items.size(); i++ ) {
    double dist = distance( target, items[i] );
    if ( heap.size() < k || dist < heap.top().dist ) {
      if (heap.size() == k) heap.pop();
      heap.push( HeapItem( i, dist ) );
    }
  }
  
  results->clear();
  distances->clear();
  while( !heap.empty() ) {
    results->push_back( items[heap.top().index] );
    distances->push_back( heap.top().dist );
    heap.pop();
  }
  
  std::reverse( results->begin(), results->end() );
  std::reverse( distances->begin(), distances->end() );
}

int do_main() {
  std::vector<VirenMyPoint> points;
  printf("Reading cities database...\n");
  FILE* file = fopen("cities.txt", "rt");
  for(;;) {
    char buffer[1000];
    VirenMyPoint point;
    if ( !fgets(buffer, 1000, file ) ) {
      fclose( file );
      break;
    }
    point.city = buffer;
    size_t comma = point.city.rfind(",");
    sscanf(buffer + comma + 1, "%lg", &point.longitude);
    comma = point.city.rfind(",", comma-1);
    sscanf(buffer + comma + 1, "%lg", &point.latitude);
      //printf("%lg, %lg\n", point.latitude, point.longitude);
    points.push_back(point);
      //if(points.size()>50000)break;
  }
  
  VpTree<VirenMyPoint, distance> tree;
  uint64_t start, end;
  QueryPerformanceCounter( &start );
  tree.create( points );
  QueryPerformanceCounter( &end );
  printf("Create took %d\n", (int)(end-start));
  
  VirenMyPoint point;
  point.latitude = 43.466438;
  point.longitude = -80.519185;
  std::vector<VirenMyPoint> results;
  std::vector<double> distances;
  
  QueryPerformanceCounter( &start );
  tree.search( point, 8, &results, &distances );
  QueryPerformanceCounter( &end );
  printf("Search took %d\n", (int)(end-start));
  
  for( int i = 0; i < results.size(); i++ ) {
    printf("%s %lg\n", results[i].city.c_str(), distances[i]);
  }
  
  printf("---\n");
  QueryPerformanceCounter( &start );
  linear_search( points, point, 8, &results, &distances );
  QueryPerformanceCounter( &end );
  printf("Linear search took %d\n", (int)(end-start));
  
  for( int i = 0; i < results.size(); i++ ) {
    printf("%s %lg\n", results[i].city.c_str(), distances[i]);
  }
  
  
  return 0;
}
#endif
  //viren-
