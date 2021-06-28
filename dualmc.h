// Copyright (C) 2017, Dominik Wodniok
// This software may be modified and distributed under the terms
// of the BSD 3-Clause license.
// See the LICENSE.txt file for details.

#ifndef DUALMC_H_INCLUDED
#define DUALMC_H_INCLUDED

/// \file   dualmc.h
/// \author Dominik Wodniok
/// \date   2009

// c includes
#include <cstdint>

// stl includes
#include <unordered_map>
#include <vector>

// In uint8_t type
class dualmc {
public:
	typedef float VertexComponentsType;
	typedef int32_t QuadIndexType;

	// vertex structure for dual points
	struct Vertex {
		// non-initializing constructor
		Vertex();

		// initializing constructor
		Vertex(VertexComponentsType x, VertexComponentsType y, VertexComponentsType z);

		// initializing constructor
		Vertex(const Vertex & v);

		// components
		VertexComponentsType x, y, z;
	};

	/// quad indices structure
	struct Quad {
		// non-initializing constructor
		Quad();

		// initializing constructor
		Quad(QuadIndexType i0, QuadIndexType i1, QuadIndexType i2, QuadIndexType i3);

		// quad indices
		QuadIndexType i0, i1, i2, i3;
	};

public:
	// typedefs
	typedef uint8_t VolumeDataType;

	/// Extracts the iso surface for a given volume and iso value.
	/// Output is a list of vertices and a list of indices, which connect
	/// vertices to quads.
	/// The quad mesh either uses shared vertex indices or is a quad soup if
	/// desired.
	void build(
		const VolumeDataType * data,
		const int32_t dimX,
		const int32_t dimY,
		const int32_t dimZ,
		const VolumeDataType iso,
		std::vector<dualmc::Vertex> & vertices,
		std::vector<dualmc::Quad> & quads
	);

private:
	/// Extract quad mesh with shared vertex indices.
	void buildSharedVerticesQuads(
		const VolumeDataType iso,
		std::vector<Vertex> & vertices,
		std::vector<Quad> & quads
	);

private:

	/// enum with edge codes for a 12-bit voxel edge mask to indicate
	/// grid edges which intersect the ISO surface of classic marching cubes
	enum DMCEdgeCode {
		EDGE0 = 1,
		EDGE1 = 1 << 1,
		EDGE2 = 1 << 2,
		EDGE3 = 1 << 3,
		EDGE4 = 1 << 4,
		EDGE5 = 1 << 5,
		EDGE6 = 1 << 6,
		EDGE7 = 1 << 7,
		EDGE8 = 1 << 8,
		EDGE9 = 1 << 9,
		EDGE10 = 1 << 10,
		EDGE11 = 1 << 11,
		FORCE_32BIT = 0xffffffff
	};

	/// get the 8-bit in-out mask for the voxel corners of the cell cube at (cx,cy,cz)
	/// and the given iso value
	int getCellCode(
		const int32_t cx,
		const int32_t cy,
		const int32_t cz,
		const VolumeDataType iso
	) const;

	/// Get the 12-bit dual point code mask, which encodes the traditional
	/// marching cube vertices of the traditional marching cubes face which
	/// corresponds to the dual point.
	/// This is also where the manifold dual marching cubes algorithm is
	/// implemented.
	int getDualPointCode(
		const int32_t cx,
		const int32_t cy,
		const int32_t cz,
		const VolumeDataType iso,
		const DMCEdgeCode edge
	) const;

	/// Given a dual point code and iso value, compute the dual point.
	void calculateDualPoint(
		const int32_t cx,
		const int32_t cy,
		const int32_t cz,
		const VolumeDataType iso,
		const int pointCode,
		Vertex &v
	) const;

	/// Get the shared index of a dual point which is uniquly identified by its
	/// cell cube index and a cube edge. The dual point is computed,
	/// if it has not been computed before.
	QuadIndexType getSharedDualPointIndex(
		const int32_t cx, 
		const int32_t cy, 
		const int32_t cz,
		const VolumeDataType iso,
		const DMCEdgeCode edge,
		std::vector<Vertex> & vertices
	);

	/// Compute a linearized cell cube index.
	int32_t gA(const int32_t x, const int32_t y, const int32_t z) const;

private:

	/// Dual Marching Cubes table
	/// Encodes the edge vertices for the 256 marching cubes cases.
	/// A marching cube case produces up to four faces and ,thus, up to four
	/// dual points.
	const int32_t dualPointsList[256][4] = {
		{0, 0, 0, 0}, // 0
		{ EDGE0 | EDGE3 | EDGE8, 0, 0, 0 }, // 1
		{ EDGE0 | EDGE1 | EDGE9, 0, 0, 0 }, // 2
		{ EDGE1 | EDGE3 | EDGE8 | EDGE9, 0, 0, 0 }, // 3
		{ EDGE4 | EDGE7 | EDGE8, 0, 0, 0 }, // 4
		{ EDGE0 | EDGE3 | EDGE4 | EDGE7, 0, 0, 0 }, // 5
		{ EDGE0 | EDGE1 | EDGE9, EDGE4 | EDGE7 | EDGE8, 0, 0 }, // 6
		{ EDGE1 | EDGE3 | EDGE4 | EDGE7 | EDGE9, 0, 0, 0 }, // 7
		{ EDGE4 | EDGE5 | EDGE9, 0, 0, 0 }, // 8
		{ EDGE0 | EDGE3 | EDGE8, EDGE4 | EDGE5 | EDGE9, 0, 0 }, // 9
		{ EDGE0 | EDGE1 | EDGE4 | EDGE5, 0, 0, 0 }, // 10
		{ EDGE1 | EDGE3 | EDGE4 | EDGE5 | EDGE8, 0, 0, 0 }, // 11
		{ EDGE5 | EDGE7 | EDGE8 | EDGE9, 0, 0, 0 }, // 12
		{ EDGE0 | EDGE3 | EDGE5 | EDGE7 | EDGE9, 0, 0, 0 }, // 13
		{ EDGE0 | EDGE1 | EDGE5 | EDGE7 | EDGE8, 0, 0, 0 }, // 14
		{ EDGE1 | EDGE3 | EDGE5 | EDGE7, 0, 0, 0 }, // 15
		{ EDGE2 | EDGE3 | EDGE11, 0, 0, 0 }, // 16
		{ EDGE0 | EDGE2 | EDGE8 | EDGE11, 0, 0, 0 }, // 17
		{ EDGE0 | EDGE1 | EDGE9, EDGE2 | EDGE3 | EDGE11, 0, 0 }, // 18
		{ EDGE1 | EDGE2 | EDGE8 | EDGE9 | EDGE11, 0, 0, 0 }, // 19
		{ EDGE4 | EDGE7 | EDGE8, EDGE2 | EDGE3 | EDGE11, 0, 0 }, // 20
		{ EDGE0 | EDGE2 | EDGE4 | EDGE7 | EDGE11, 0, 0, 0 }, // 21
		{ EDGE0 | EDGE1 | EDGE9, EDGE4 | EDGE7 | EDGE8, EDGE2 | EDGE3 | EDGE11, 0 }, // 22
		{ EDGE1 | EDGE2 | EDGE4 | EDGE7 | EDGE9 | EDGE11, 0, 0, 0 }, // 23
		{ EDGE4 | EDGE5 | EDGE9, EDGE2 | EDGE3 | EDGE11, 0, 0 }, // 24
		{ EDGE0 | EDGE2 | EDGE8 | EDGE11, EDGE4 | EDGE5 | EDGE9, 0, 0 }, // 25
		{ EDGE0 | EDGE1 | EDGE4 | EDGE5, EDGE2 | EDGE3 | EDGE11, 0, 0 }, // 26
		{ EDGE1 | EDGE2 | EDGE4 | EDGE5 | EDGE8 | EDGE11, 0, 0, 0 }, // 27
		{ EDGE5 | EDGE7 | EDGE8 | EDGE9, EDGE2 | EDGE3 | EDGE11, 0, 0 }, // 28
		{ EDGE0 | EDGE2 | EDGE5 | EDGE7 | EDGE9 | EDGE11, 0, 0, 0 }, // 29
		{ EDGE0 | EDGE1 | EDGE5 | EDGE7 | EDGE8, EDGE2 | EDGE3 | EDGE11, 0, 0 }, // 30
		{ EDGE1 | EDGE2 | EDGE5 | EDGE7 | EDGE11, 0, 0, 0 }, // 31
		{ EDGE1 | EDGE2 | EDGE10, 0, 0, 0 }, // 32
		{ EDGE0 | EDGE3 | EDGE8, EDGE1 | EDGE2 | EDGE10, 0, 0 }, // 33
		{ EDGE0 | EDGE2 | EDGE9 | EDGE10, 0, 0, 0 }, // 34
		{ EDGE2 | EDGE3 | EDGE8 | EDGE9 | EDGE10, 0, 0, 0 }, // 35
		{ EDGE4 | EDGE7 | EDGE8, EDGE1 | EDGE2 | EDGE10, 0, 0 }, // 36
		{ EDGE0 | EDGE3 | EDGE4 | EDGE7, EDGE1 | EDGE2 | EDGE10, 0, 0 }, // 37
		{ EDGE0 | EDGE2 | EDGE9 | EDGE10, EDGE4 | EDGE7 | EDGE8, 0, 0 }, // 38
		{ EDGE2 | EDGE3 | EDGE4 | EDGE7 | EDGE9 | EDGE10, 0, 0, 0 }, // 39
		{ EDGE4 | EDGE5 | EDGE9, EDGE1 | EDGE2 | EDGE10, 0, 0 }, // 40
		{ EDGE0 | EDGE3 | EDGE8, EDGE4 | EDGE5 | EDGE9, EDGE1 | EDGE2 | EDGE10, 0 }, // 41
		{ EDGE0 | EDGE2 | EDGE4 | EDGE5 | EDGE10, 0, 0, 0 }, // 42
		{ EDGE2 | EDGE3 | EDGE4 | EDGE5 | EDGE8 | EDGE10, 0, 0, 0 }, // 43
		{ EDGE5 | EDGE7 | EDGE8 | EDGE9, EDGE1 | EDGE2 | EDGE10, 0, 0 }, // 44
		{ EDGE0 | EDGE3 | EDGE5 | EDGE7 | EDGE9, EDGE1 | EDGE2 | EDGE10, 0, 0 }, // 45
		{ EDGE0 | EDGE2 | EDGE5 | EDGE7 | EDGE8 | EDGE10, 0, 0, 0 }, // 46
		{ EDGE2 | EDGE3 | EDGE5 | EDGE7 | EDGE10, 0, 0, 0 }, // 47
		{ EDGE1 | EDGE3 | EDGE10 | EDGE11, 0, 0, 0 }, // 48
		{ EDGE0 | EDGE1 | EDGE8 | EDGE10 | EDGE11, 0, 0, 0 }, // 49
		{ EDGE0 | EDGE3 | EDGE9 | EDGE10 | EDGE11, 0, 0, 0 }, // 50
		{ EDGE8 | EDGE9 | EDGE10 | EDGE11, 0, 0, 0 }, // 51
		{ EDGE4 | EDGE7 | EDGE8, EDGE1 | EDGE3 | EDGE10 | EDGE11, 0, 0 }, // 52
		{ EDGE0 | EDGE1 | EDGE4 | EDGE7 | EDGE10 | EDGE11, 0, 0, 0 }, // 53
		{ EDGE0 | EDGE3 | EDGE9 | EDGE10 | EDGE11, EDGE4 | EDGE7 | EDGE8, 0, 0 }, // 54
		{ EDGE4 | EDGE7 | EDGE9 | EDGE10 | EDGE11, 0, 0, 0 }, // 55
		{ EDGE4 | EDGE5 | EDGE9, EDGE1 | EDGE3 | EDGE10 | EDGE11, 0, 0 }, // 56
		{ EDGE0 | EDGE1 | EDGE8 | EDGE10 | EDGE11, EDGE4 | EDGE5 | EDGE9, 0, 0 }, // 57
		{ EDGE0 | EDGE3 | EDGE4 | EDGE5 | EDGE10 | EDGE11, 0, 0, 0 }, // 58
		{ EDGE4 | EDGE5 | EDGE8 | EDGE10 | EDGE11, 0, 0, 0 }, // 59
		{ EDGE5 | EDGE7 | EDGE8 | EDGE9, EDGE1 | EDGE3 | EDGE10 | EDGE11, 0, 0 }, // 60
		{ EDGE0 | EDGE1 | EDGE5 | EDGE7 | EDGE9 | EDGE10 | EDGE11, 0, 0, 0 }, // 61
		{ EDGE0 | EDGE3 | EDGE5 | EDGE7 | EDGE8 | EDGE10 | EDGE11, 0, 0, 0 }, // 62
		{ EDGE5 | EDGE7 | EDGE10 | EDGE11, 0, 0, 0 }, // 63
		{ EDGE6 | EDGE7 | EDGE11, 0, 0, 0 }, // 64
		{ EDGE0 | EDGE3 | EDGE8, EDGE6 | EDGE7 | EDGE11, 0, 0 }, // 65
		{ EDGE0 | EDGE1 | EDGE9, EDGE6 | EDGE7 | EDGE11, 0, 0 }, // 66
		{ EDGE1 | EDGE3 | EDGE8 | EDGE9, EDGE6 | EDGE7 | EDGE11, 0, 0 }, // 67
		{ EDGE4 | EDGE6 | EDGE8 | EDGE11, 0, 0, 0 }, // 68
		{ EDGE0 | EDGE3 | EDGE4 | EDGE6 | EDGE11, 0, 0, 0 }, // 69
		{ EDGE0 | EDGE1 | EDGE9, EDGE4 | EDGE6 | EDGE8 | EDGE11, 0, 0 }, // 70
		{ EDGE1 | EDGE3 | EDGE4 | EDGE6 | EDGE9 | EDGE11, 0, 0, 0 }, // 71
		{ EDGE4 | EDGE5 | EDGE9, EDGE6 | EDGE7 | EDGE11, 0, 0 }, // 72
		{ EDGE0 | EDGE3 | EDGE8, EDGE4 | EDGE5 | EDGE9, EDGE6 | EDGE7 | EDGE11, 0 }, // 73
		{ EDGE0 | EDGE1 | EDGE4 | EDGE5, EDGE6 | EDGE7 | EDGE11, 0, 0 }, // 74
		{ EDGE1 | EDGE3 | EDGE4 | EDGE5 | EDGE8, EDGE6 | EDGE7 | EDGE11, 0, 0 }, // 75
		{ EDGE5 | EDGE6 | EDGE8 | EDGE9 | EDGE11, 0, 0, 0 }, // 76
		{ EDGE0 | EDGE3 | EDGE5 | EDGE6 | EDGE9 | EDGE11, 0, 0, 0 }, // 77
		{ EDGE0 | EDGE1 | EDGE5 | EDGE6 | EDGE8 | EDGE11, 0, 0, 0 }, // 78
		{ EDGE1 | EDGE3 | EDGE5 | EDGE6 | EDGE11, 0, 0, 0 }, // 79
		{ EDGE2 | EDGE3 | EDGE6 | EDGE7, 0, 0, 0 }, // 80
		{ EDGE0 | EDGE2 | EDGE6 | EDGE7 | EDGE8, 0, 0, 0 }, // 81
		{ EDGE0 | EDGE1 | EDGE9, EDGE2 | EDGE3 | EDGE6 | EDGE7, 0, 0 }, // 82
		{ EDGE1 | EDGE2 | EDGE6 | EDGE7 | EDGE8 | EDGE9, 0, 0, 0 }, // 83
		{ EDGE2 | EDGE3 | EDGE4 | EDGE6 | EDGE8, 0, 0, 0 }, // 84
		{ EDGE0 | EDGE2 | EDGE4 | EDGE6, 0, 0, 0 }, // 85
		{ EDGE0 | EDGE1 | EDGE9, EDGE2 | EDGE3 | EDGE4 | EDGE6 | EDGE8, 0, 0 }, // 86
		{ EDGE1 | EDGE2 | EDGE4 | EDGE6 | EDGE9, 0, 0, 0 }, // 87
		{ EDGE4 | EDGE5 | EDGE9, EDGE2 | EDGE3 | EDGE6 | EDGE7, 0, 0 }, // 88
		{ EDGE0 | EDGE2 | EDGE6 | EDGE7 | EDGE8, EDGE4 | EDGE5 | EDGE9, 0, 0 }, // 89
		{ EDGE0 | EDGE1 | EDGE4 | EDGE5, EDGE2 | EDGE3 | EDGE6 | EDGE7, 0, 0 }, // 90
		{ EDGE1 | EDGE2 | EDGE4 | EDGE5 | EDGE6 | EDGE7 | EDGE8, 0, 0, 0 }, // 91
		{ EDGE2 | EDGE3 | EDGE5 | EDGE6 | EDGE8 | EDGE9, 0, 0, 0 }, // 92
		{ EDGE0 | EDGE2 | EDGE5 | EDGE6 | EDGE9, 0, 0, 0 }, // 93
		{ EDGE0 | EDGE1 | EDGE2 | EDGE3 | EDGE5 | EDGE6 | EDGE8, 0, 0, 0 }, // 94
		{ EDGE1 | EDGE2 | EDGE5 | EDGE6, 0, 0, 0 }, // 95
		{ EDGE1 | EDGE2 | EDGE10, EDGE6 | EDGE7 | EDGE11, 0, 0 }, // 96
		{ EDGE0 | EDGE3 | EDGE8, EDGE1 | EDGE2 | EDGE10, EDGE6 | EDGE7 | EDGE11, 0 }, // 97
		{ EDGE0 | EDGE2 | EDGE9 | EDGE10, EDGE6 | EDGE7 | EDGE11, 0, 0 }, // 98
		{ EDGE2 | EDGE3 | EDGE8 | EDGE9 | EDGE10, EDGE6 | EDGE7 | EDGE11, 0, 0 }, // 99
		{ EDGE4 | EDGE6 | EDGE8 | EDGE11, EDGE1 | EDGE2 | EDGE10, 0, 0 }, // 100
		{ EDGE0 | EDGE3 | EDGE4 | EDGE6 | EDGE11, EDGE1 | EDGE2 | EDGE10, 0, 0 }, // 101
		{ EDGE0 | EDGE2 | EDGE9 | EDGE10, EDGE4 | EDGE6 | EDGE8 | EDGE11, 0, 0 }, // 102
		{ EDGE2 | EDGE3 | EDGE4 | EDGE6 | EDGE9 | EDGE10 | EDGE11, 0, 0, 0 }, // 103
		{ EDGE4 | EDGE5 | EDGE9, EDGE1 | EDGE2 | EDGE10, EDGE6 | EDGE7 | EDGE11, 0 }, // 104
		{ EDGE0 | EDGE3 | EDGE8, EDGE4 | EDGE5 | EDGE9, EDGE1 | EDGE2 | EDGE10, EDGE6 | EDGE7 | EDGE11 }, // 105
		{ EDGE0 | EDGE2 | EDGE4 | EDGE5 | EDGE10, EDGE6 | EDGE7 | EDGE11, 0, 0 }, // 106
		{ EDGE2 | EDGE3 | EDGE4 | EDGE5 | EDGE8 | EDGE10, EDGE6 | EDGE7 | EDGE11, 0, 0 }, // 107
		{ EDGE5 | EDGE6 | EDGE8 | EDGE9 | EDGE11, EDGE1 | EDGE2 | EDGE10, 0, 0 }, // 108
		{ EDGE0 | EDGE3 | EDGE5 | EDGE6 | EDGE9 | EDGE11, EDGE1 | EDGE2 | EDGE10, 0, 0 }, // 109
		{ EDGE0 | EDGE2 | EDGE5 | EDGE6 | EDGE8 | EDGE10 | EDGE11, 0, 0, 0 }, // 110
		{ EDGE2 | EDGE3 | EDGE5 | EDGE6 | EDGE10 | EDGE11, 0, 0, 0 }, // 111
		{ EDGE1 | EDGE3 | EDGE6 | EDGE7 | EDGE10, 0, 0, 0 }, // 112
		{ EDGE0 | EDGE1 | EDGE6 | EDGE7 | EDGE8 | EDGE10, 0, 0, 0 }, // 113
		{ EDGE0 | EDGE3 | EDGE6 | EDGE7 | EDGE9 | EDGE10, 0, 0, 0 }, // 114
		{ EDGE6 | EDGE7 | EDGE8 | EDGE9 | EDGE10, 0, 0, 0 }, // 115
		{ EDGE1 | EDGE3 | EDGE4 | EDGE6 | EDGE8 | EDGE10, 0, 0, 0 }, // 116
		{ EDGE0 | EDGE1 | EDGE4 | EDGE6 | EDGE10, 0, 0, 0 }, // 117
		{ EDGE0 | EDGE3 | EDGE4 | EDGE6 | EDGE8 | EDGE9 | EDGE10, 0, 0, 0 }, // 118
		{ EDGE4 | EDGE6 | EDGE9 | EDGE10, 0, 0, 0 }, // 119
		{ EDGE4 | EDGE5 | EDGE9, EDGE1 | EDGE3 | EDGE6 | EDGE7 | EDGE10, 0, 0 }, // 120
		{ EDGE0 | EDGE1 | EDGE6 | EDGE7 | EDGE8 | EDGE10, EDGE4 | EDGE5 | EDGE9, 0, 0 }, // 121
		{ EDGE0 | EDGE3 | EDGE4 | EDGE5 | EDGE6 | EDGE7 | EDGE10, 0, 0, 0 }, // 122
		{ EDGE4 | EDGE5 | EDGE6 | EDGE7 | EDGE8 | EDGE10, 0, 0, 0 }, // 123
		{ EDGE1 | EDGE3 | EDGE5 | EDGE6 | EDGE8 | EDGE9 | EDGE10, 0, 0, 0 }, // 124
		{ EDGE0 | EDGE1 | EDGE5 | EDGE6 | EDGE9 | EDGE10, 0, 0, 0 }, // 125
		{ EDGE0 | EDGE3 | EDGE8, EDGE5 | EDGE6 | EDGE10, 0, 0 }, // 126
		{ EDGE5 | EDGE6 | EDGE10, 0, 0, 0 }, // 127
		{ EDGE5 | EDGE6 | EDGE10, 0, 0, 0 }, // 128
		{ EDGE0 | EDGE3 | EDGE8, EDGE5 | EDGE6 | EDGE10, 0, 0 }, // 129
		{ EDGE0 | EDGE1 | EDGE9, EDGE5 | EDGE6 | EDGE10, 0, 0 }, // 130
		{ EDGE1 | EDGE3 | EDGE8 | EDGE9, EDGE5 | EDGE6 | EDGE10, 0, 0 }, // 131
		{ EDGE4 | EDGE7 | EDGE8, EDGE5 | EDGE6 | EDGE10, 0, 0 }, // 132
		{ EDGE0 | EDGE3 | EDGE4 | EDGE7, EDGE5 | EDGE6 | EDGE10, 0, 0 }, // 133
		{ EDGE0 | EDGE1 | EDGE9, EDGE4 | EDGE7 | EDGE8, EDGE5 | EDGE6 | EDGE10, 0 }, // 134
		{ EDGE1 | EDGE3 | EDGE4 | EDGE7 | EDGE9, EDGE5 | EDGE6 | EDGE10, 0, 0 }, // 135
		{ EDGE4 | EDGE6 | EDGE9 | EDGE10, 0, 0, 0 }, // 136
		{ EDGE0 | EDGE3 | EDGE8, EDGE4 | EDGE6 | EDGE9 | EDGE10, 0, 0 }, // 137
		{ EDGE0 | EDGE1 | EDGE4 | EDGE6 | EDGE10, 0, 0, 0 }, // 138
		{ EDGE1 | EDGE3 | EDGE4 | EDGE6 | EDGE8 | EDGE10, 0, 0, 0 }, // 139
		{ EDGE6 | EDGE7 | EDGE8 | EDGE9 | EDGE10, 0, 0, 0 }, // 140
		{ EDGE0 | EDGE3 | EDGE6 | EDGE7 | EDGE9 | EDGE10, 0, 0, 0 }, // 141
		{ EDGE0 | EDGE1 | EDGE6 | EDGE7 | EDGE8 | EDGE10, 0, 0, 0 }, // 142
		{ EDGE1 | EDGE3 | EDGE6 | EDGE7 | EDGE10, 0, 0, 0 }, // 143
		{ EDGE2 | EDGE3 | EDGE11, EDGE5 | EDGE6 | EDGE10, 0, 0 }, // 144
		{ EDGE0 | EDGE2 | EDGE8 | EDGE11, EDGE5 | EDGE6 | EDGE10, 0, 0 }, // 145
		{ EDGE0 | EDGE1 | EDGE9, EDGE2 | EDGE3 | EDGE11, EDGE5 | EDGE6 | EDGE10, 0 }, // 146
		{ EDGE1 | EDGE2 | EDGE8 | EDGE9 | EDGE11, EDGE5 | EDGE6 | EDGE10, 0, 0 }, // 147
		{ EDGE4 | EDGE7 | EDGE8, EDGE2 | EDGE3 | EDGE11, EDGE5 | EDGE6 | EDGE10, 0 }, // 148
		{ EDGE0 | EDGE2 | EDGE4 | EDGE7 | EDGE11, EDGE5 | EDGE6 | EDGE10, 0, 0 }, // 149
		{ EDGE0 | EDGE1 | EDGE9, EDGE4 | EDGE7 | EDGE8, EDGE2 | EDGE3 | EDGE11, EDGE5 | EDGE6 | EDGE10 }, // 150
		{ EDGE1 | EDGE2 | EDGE4 | EDGE7 | EDGE9 | EDGE11, EDGE5 | EDGE6 | EDGE10, 0, 0 }, // 151
		{ EDGE4 | EDGE6 | EDGE9 | EDGE10, EDGE2 | EDGE3 | EDGE11, 0, 0 }, // 152
		{ EDGE0 | EDGE2 | EDGE8 | EDGE11, EDGE4 | EDGE6 | EDGE9 | EDGE10, 0, 0 }, // 153
		{ EDGE0 | EDGE1 | EDGE4 | EDGE6 | EDGE10, EDGE2 | EDGE3 | EDGE11, 0, 0 }, // 154
		{ EDGE1 | EDGE2 | EDGE4 | EDGE6 | EDGE8 | EDGE10 | EDGE11, 0, 0, 0 }, // 155
		{ EDGE6 | EDGE7 | EDGE8 | EDGE9 | EDGE10, EDGE2 | EDGE3 | EDGE11, 0, 0 }, // 156
		{ EDGE0 | EDGE2 | EDGE6 | EDGE7 | EDGE9 | EDGE10 | EDGE11, 0, 0, 0 }, // 157
		{ EDGE0 | EDGE1 | EDGE6 | EDGE7 | EDGE8 | EDGE10, EDGE2 | EDGE3 | EDGE11, 0, 0 }, // 158
		{ EDGE1 | EDGE2 | EDGE6 | EDGE7 | EDGE10 | EDGE11, 0, 0, 0 }, // 159
		{ EDGE1 | EDGE2 | EDGE5 | EDGE6, 0, 0, 0 }, // 160
		{ EDGE0 | EDGE3 | EDGE8, EDGE1 | EDGE2 | EDGE5 | EDGE6, 0, 0 }, // 161
		{ EDGE0 | EDGE2 | EDGE5 | EDGE6 | EDGE9, 0, 0, 0 }, // 162
		{ EDGE2 | EDGE3 | EDGE5 | EDGE6 | EDGE8 | EDGE9, 0, 0, 0 }, // 163
		{ EDGE4 | EDGE7 | EDGE8, EDGE1 | EDGE2 | EDGE5 | EDGE6, 0, 0 }, // 164
		{ EDGE0 | EDGE3 | EDGE4 | EDGE7, EDGE1 | EDGE2 | EDGE5 | EDGE6, 0, 0 }, // 165
		{ EDGE0 | EDGE2 | EDGE5 | EDGE6 | EDGE9, EDGE4 | EDGE7 | EDGE8, 0, 0 }, // 166
		{ EDGE2 | EDGE3 | EDGE4 | EDGE5 | EDGE6 | EDGE7 | EDGE9, 0, 0, 0 }, // 167
		{ EDGE1 | EDGE2 | EDGE4 | EDGE6 | EDGE9, 0, 0, 0 }, // 168
		{ EDGE0 | EDGE3 | EDGE8, EDGE1 | EDGE2 | EDGE4 | EDGE6 | EDGE9, 0, 0 }, // 169
		{ EDGE0 | EDGE2 | EDGE4 | EDGE6, 0, 0, 0 }, // 170
		{ EDGE2 | EDGE3 | EDGE4 | EDGE6 | EDGE8, 0, 0, 0 }, // 171
		{ EDGE1 | EDGE2 | EDGE6 | EDGE7 | EDGE8 | EDGE9, 0, 0, 0 }, // 172
		{ EDGE0 | EDGE1 | EDGE2 | EDGE3 | EDGE6 | EDGE7 | EDGE9, 0, 0, 0 }, // 173
		{ EDGE0 | EDGE2 | EDGE6 | EDGE7 | EDGE8, 0, 0, 0 }, // 174
		{ EDGE2 | EDGE3 | EDGE6 | EDGE7, 0, 0, 0 }, // 175
		{ EDGE1 | EDGE3 | EDGE5 | EDGE6 | EDGE11, 0, 0, 0 }, // 176
		{ EDGE0 | EDGE1 | EDGE5 | EDGE6 | EDGE8 | EDGE11, 0, 0, 0 }, // 177
		{ EDGE0 | EDGE3 | EDGE5 | EDGE6 | EDGE9 | EDGE11, 0, 0, 0 }, // 178
		{ EDGE5 | EDGE6 | EDGE8 | EDGE9 | EDGE11, 0, 0, 0 }, // 179
		{ EDGE4 | EDGE7 | EDGE8, EDGE1 | EDGE3 | EDGE5 | EDGE6 | EDGE11, 0, 0 }, // 180
		{ EDGE0 | EDGE1 | EDGE4 | EDGE5 | EDGE6 | EDGE7 | EDGE11, 0, 0, 0 }, // 181
		{ EDGE0 | EDGE3 | EDGE5 | EDGE6 | EDGE9 | EDGE11, EDGE4 | EDGE7 | EDGE8, 0, 0 }, // 182
		{ EDGE4 | EDGE5 | EDGE6 | EDGE7 | EDGE9 | EDGE11, 0, 0, 0 }, // 183
		{ EDGE1 | EDGE3 | EDGE4 | EDGE6 | EDGE9 | EDGE11, 0, 0, 0 }, // 184
		{ EDGE0 | EDGE1 | EDGE4 | EDGE6 | EDGE8 | EDGE9 | EDGE11, 0, 0, 0 }, // 185
		{ EDGE0 | EDGE3 | EDGE4 | EDGE6 | EDGE11, 0, 0, 0 }, // 186
		{ EDGE4 | EDGE6 | EDGE8 | EDGE11, 0, 0, 0 }, // 187
		{ EDGE1 | EDGE3 | EDGE6 | EDGE7 | EDGE8 | EDGE9 | EDGE11, 0, 0, 0 }, // 188
		{ EDGE0 | EDGE1 | EDGE9, EDGE6 | EDGE7 | EDGE11, 0, 0 }, // 189
		{ EDGE0 | EDGE3 | EDGE6 | EDGE7 | EDGE8 | EDGE11, 0, 0, 0 }, // 190
		{ EDGE6 | EDGE7 | EDGE11, 0, 0, 0 }, // 191
		{ EDGE5 | EDGE7 | EDGE10 | EDGE11, 0, 0, 0 }, // 192
		{ EDGE0 | EDGE3 | EDGE8, EDGE5 | EDGE7 | EDGE10 | EDGE11, 0, 0 }, // 193
		{ EDGE0 | EDGE1 | EDGE9, EDGE5 | EDGE7 | EDGE10 | EDGE11, 0, 0 }, // 194
		{ EDGE1 | EDGE3 | EDGE8 | EDGE9, EDGE5 | EDGE7 | EDGE10 | EDGE11, 0, 0 }, // 195
		{ EDGE4 | EDGE5 | EDGE8 | EDGE10 | EDGE11, 0, 0, 0 }, // 196
		{ EDGE0 | EDGE3 | EDGE4 | EDGE5 | EDGE10 | EDGE11, 0, 0, 0 }, // 197
		{ EDGE0 | EDGE1 | EDGE9, EDGE4 | EDGE5 | EDGE8 | EDGE10 | EDGE11, 0, 0 }, // 198
		{ EDGE1 | EDGE3 | EDGE4 | EDGE5 | EDGE9 | EDGE10 | EDGE11, 0, 0, 0 }, // 199
		{ EDGE4 | EDGE7 | EDGE9 | EDGE10 | EDGE11, 0, 0, 0 }, // 200
		{ EDGE0 | EDGE3 | EDGE8, EDGE4 | EDGE7 | EDGE9 | EDGE10 | EDGE11, 0, 0 }, // 201
		{ EDGE0 | EDGE1 | EDGE4 | EDGE7 | EDGE10 | EDGE11, 0, 0, 0 }, // 202
		{ EDGE1 | EDGE3 | EDGE4 | EDGE7 | EDGE8 | EDGE10 | EDGE11, 0, 0, 0 }, // 203
		{ EDGE8 | EDGE9 | EDGE10 | EDGE11, 0, 0, 0 }, // 204
		{ EDGE0 | EDGE3 | EDGE9 | EDGE10 | EDGE11, 0, 0, 0 }, // 205
		{ EDGE0 | EDGE1 | EDGE8 | EDGE10 | EDGE11, 0, 0, 0 }, // 206
		{ EDGE1 | EDGE3 | EDGE10 | EDGE11, 0, 0, 0 }, // 207
		{ EDGE2 | EDGE3 | EDGE5 | EDGE7 | EDGE10, 0, 0, 0 }, // 208
		{ EDGE0 | EDGE2 | EDGE5 | EDGE7 | EDGE8 | EDGE10, 0, 0, 0 }, // 209
		{ EDGE0 | EDGE1 | EDGE9, EDGE2 | EDGE3 | EDGE5 | EDGE7 | EDGE10, 0, 0 }, // 210
		{ EDGE1 | EDGE2 | EDGE5 | EDGE7 | EDGE8 | EDGE9 | EDGE10, 0, 0, 0 }, // 211
		{ EDGE2 | EDGE3 | EDGE4 | EDGE5 | EDGE8 | EDGE10, 0, 0, 0 }, // 212
		{ EDGE0 | EDGE2 | EDGE4 | EDGE5 | EDGE10, 0, 0, 0 }, // 213
		{ EDGE0 | EDGE1 | EDGE9, EDGE2 | EDGE3 | EDGE4 | EDGE5 | EDGE8 | EDGE10, 0, 0 }, // 214
		{ EDGE1 | EDGE2 | EDGE4 | EDGE5 | EDGE9 | EDGE10, 0, 0, 0 }, // 215
		{ EDGE2 | EDGE3 | EDGE4 | EDGE7 | EDGE9 | EDGE10, 0, 0, 0 }, // 216
		{ EDGE0 | EDGE2 | EDGE4 | EDGE7 | EDGE8 | EDGE9 | EDGE10, 0, 0, 0 }, // 217
		{ EDGE0 | EDGE1 | EDGE2 | EDGE3 | EDGE4 | EDGE7 | EDGE10, 0, 0, 0 }, // 218
		{ EDGE4 | EDGE7 | EDGE8, EDGE1 | EDGE2 | EDGE10, 0, 0 }, // 219
		{ EDGE2 | EDGE3 | EDGE8 | EDGE9 | EDGE10, 0, 0, 0 }, // 220
		{ EDGE0 | EDGE2 | EDGE9 | EDGE10, 0, 0, 0 }, // 221
		{ EDGE0 | EDGE1 | EDGE2 | EDGE3 | EDGE8 | EDGE10, 0, 0, 0 }, // 222
		{ EDGE1 | EDGE2 | EDGE10, 0, 0, 0 }, // 223
		{ EDGE1 | EDGE2 | EDGE5 | EDGE7 | EDGE11, 0, 0, 0 }, // 224
		{ EDGE0 | EDGE3 | EDGE8, EDGE1 | EDGE2 | EDGE5 | EDGE7 | EDGE11, 0, 0 }, // 225
		{ EDGE0 | EDGE2 | EDGE5 | EDGE7 | EDGE9 | EDGE11, 0, 0, 0 }, // 226
		{ EDGE2 | EDGE3 | EDGE5 | EDGE7 | EDGE8 | EDGE9 | EDGE11, 0, 0, 0 }, // 227
		{ EDGE1 | EDGE2 | EDGE4 | EDGE5 | EDGE8 | EDGE11, 0, 0, 0 }, // 228
		{ EDGE0 | EDGE1 | EDGE2 | EDGE3 | EDGE4 | EDGE5 | EDGE11, 0, 0, 0 }, // 229
		{ EDGE0 | EDGE2 | EDGE4 | EDGE5 | EDGE8 | EDGE9 | EDGE11, 0, 0, 0 }, // 230
		{ EDGE4 | EDGE5 | EDGE9, EDGE2 | EDGE3 | EDGE11, 0, 0 }, // 231
		{ EDGE1 | EDGE2 | EDGE4 | EDGE7 | EDGE9 | EDGE11, 0, 0, 0 }, // 232
		{ EDGE0 | EDGE3 | EDGE8, EDGE1 | EDGE2 | EDGE4 | EDGE7 | EDGE9 | EDGE11, 0, 0 }, // 233
		{ EDGE0 | EDGE2 | EDGE4 | EDGE7 | EDGE11, 0, 0, 0 }, // 234
		{ EDGE2 | EDGE3 | EDGE4 | EDGE7 | EDGE8 | EDGE11, 0, 0, 0 }, // 235
		{ EDGE1 | EDGE2 | EDGE8 | EDGE9 | EDGE11, 0, 0, 0 }, // 236
		{ EDGE0 | EDGE1 | EDGE2 | EDGE3 | EDGE9 | EDGE11, 0, 0, 0 }, // 237
		{ EDGE0 | EDGE2 | EDGE8 | EDGE11, 0, 0, 0 }, // 238
		{ EDGE2 | EDGE3 | EDGE11, 0, 0, 0 }, // 239
		{ EDGE1 | EDGE3 | EDGE5 | EDGE7, 0, 0, 0 }, // 240
		{ EDGE0 | EDGE1 | EDGE5 | EDGE7 | EDGE8, 0, 0, 0 }, // 241
		{ EDGE0 | EDGE3 | EDGE5 | EDGE7 | EDGE9, 0, 0, 0 }, // 242
		{ EDGE5 | EDGE7 | EDGE8 | EDGE9, 0, 0, 0 }, // 243
		{ EDGE1 | EDGE3 | EDGE4 | EDGE5 | EDGE8, 0, 0, 0 }, // 244
		{ EDGE0 | EDGE1 | EDGE4 | EDGE5, 0, 0, 0 }, // 245
		{ EDGE0 | EDGE3 | EDGE4 | EDGE5 | EDGE8 | EDGE9, 0, 0, 0 }, // 246
		{ EDGE4 | EDGE5 | EDGE9, 0, 0, 0 }, // 247
		{ EDGE1 | EDGE3 | EDGE4 | EDGE7 | EDGE9, 0, 0, 0 }, // 248
		{ EDGE0 | EDGE1 | EDGE4 | EDGE7 | EDGE8 | EDGE9, 0, 0, 0 }, // 249
		{ EDGE0 | EDGE3 | EDGE4 | EDGE7, 0, 0, 0 }, // 250
		{ EDGE4 | EDGE7 | EDGE8, 0, 0, 0 }, // 251
		{ EDGE1 | EDGE3 | EDGE8 | EDGE9, 0, 0, 0 }, // 252
		{ EDGE0 | EDGE1 | EDGE9, 0, 0, 0 }, // 253
		{ EDGE0 | EDGE3 | EDGE8, 0, 0, 0 }, // 254
		{ 0, 0, 0, 0 } // 255
	};

	/// Table which encodes the ambiguous face of cube configurations, which
	/// can cause non-manifold meshes.
	/// Needed for manifold dual marching cubes.
	const uint8_t problematicConfigs[256] = {
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,1,0,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,3,255,255,2,255,
255,255,255,255,255,255,255,5,255,255,255,255,255,255,5,5,
255,255,255,255,255,255,4,255,255,255,3,3,1,1,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,5,255,5,255,5,
255,255,255,255,255,255,255,3,255,255,255,255,255,2,255,255,
255,255,255,255,255,3,255,3,255,4,255,255,0,255,0,255,
255,255,255,255,255,255,255,1,255,255,255,0,255,255,255,255,
255,255,255,1,255,255,255,1,255,4,2,255,255,255,2,255,
255,255,255,0,255,2,4,255,255,255,255,0,255,2,255,255,
255,255,255,255,255,255,4,255,255,4,255,255,255,255,255,255
	};

private:

	/// convenience volume extent array for x-,y-, and z-dimension
	int32_t dims[3];

	/// convenience volume data point
	const VolumeDataType * data;

	/// Dual point key structure for hashing of shared vertices
	struct DualPointKey {
		// a dual point can be uniquely identified by ite linearized volume cell
		// id and point code
		int32_t linearizedCellID;
		int pointCode;
		/// Equal operator for unordered map
		bool operator==(const DualPointKey & other) const;
	};

	/// Functor for dual point key hash generation
	struct DualPointKeyHash {
		size_t operator()(const DualPointKey & k) const {
			return size_t(k.linearizedCellID) | (size_t(k.pointCode) << 32u);
		}
	};

	/// Hash map for shared vertex index computations
	std::unordered_map<DualPointKey, QuadIndexType, DualPointKeyHash> pointToIndex;
};

// inline function definitions
//------------------------------------------------------------------------------

inline dualmc::Vertex::Vertex() {}

//------------------------------------------------------------------------------

inline dualmc::Vertex::Vertex(
	VertexComponentsType x,
	VertexComponentsType y,
	VertexComponentsType z
) : x(x), y(y), z(z) {}

//------------------------------------------------------------------------------

inline dualmc::Vertex::Vertex(const Vertex & v) : x(v.x), y(v.y), z(v.z) {}

//------------------------------------------------------------------------------

inline dualmc::Quad::Quad() {}

//------------------------------------------------------------------------------

inline dualmc::Quad::Quad(
	QuadIndexType i0,
	QuadIndexType i1,
	QuadIndexType i2,
	QuadIndexType i3
) : i0(i0), i1(i1), i2(i2), i3(i3) {}

//------------------------------------------------------------------------------

inline int32_t dualmc::gA(const int32_t x, const int32_t y, const int32_t z) const {
	return x + dims[0] * (y + dims[1] * z);
}

//------------------------------------------------------------------------------
inline bool dualmc::DualPointKey::operator==(const dualmc::DualPointKey & other) const {
	return linearizedCellID == other.linearizedCellID && pointCode == other.pointCode;
}

// END
#endif // DUALMC_H_INCLUDED
