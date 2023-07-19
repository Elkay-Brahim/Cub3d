/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_gpt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:30:31 by bchifour          #+#    #+#             */
/*   Updated: 2023/07/19 09:30:33 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    Point start;
    Point dir;
} Ray;

typedef struct {
    Point start;
    Point end;
} LineSegment;

int intersect(Ray ray, LineSegment segment, Point* intersection) {
    float x1 = segment.start.x;
    float y1 = segment.start.y;
    float x2 = segment.end.x;
    float y2 = segment.end.y;
    float x3 = ray.start.x;
    float y3 = ray.start.y;
    float x4 = ray.start.x + ray.dir.x;
    float y4 = ray.start.y + ray.dir.y;
    
    float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    
    if (denominator == 0) {
        return 0;  // No intersection
    }
    
    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
    float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denominator;
    
    if (t >= 0 && t <= 1 && u >= 0) {
        intersection->x = x1 + t * (x2 - x1);
        intersection->y = y1 + t * (y2 - y1);
        return 1;  // Intersection found
    }
    
    return 0;  // No intersection
}

int main() {
    Ray ray;
    ray.start.x = 1.0;
    ray.start.y = 1.0;
    ray.dir.x = 0.5;
    ray.dir.y = 1.0;
    
    LineSegment segment;
    segment.start.x = 0.0;
    segment.start.y = 0.0;
    segment.end.x = 2.0;
    segment.end.y = 2.0;
    
    Point intersection;
    
    if (intersect(ray, segment, &intersection)) {
        printf("Intersection at (%.2f, %.2f)\n", intersection.x, intersection.y);
    } else {
        printf("No intersection\n");
    }
    
    return 0;
}
