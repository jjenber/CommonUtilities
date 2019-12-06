#pragma once
#define MAX(_A, _B) (_A) > (_B) ? (_A) : (_B)

#define MIN(_A, _B) (_A) < (_B) ? (_A) : (_B)

#define CLAMP(_VALUE, _MIN, _MAX)								\
	(_VALUE) > (MAX((_MIN), (_MAX))) ? (MAX((_MIN), (_MAX))) :	\
	(_VALUE) < (MIN((_MIN), (_MAX))) ? (MIN((_MIN), (_MAX))) :	\
	(_VALUE);


#define SAFE_DELETE(_P) \
delete _P; \
_P = nullptr;

#define SAFE_DELETE_NATIVE_ARRAY(_P) \
delete[] _P; \
_P = nullptr;
