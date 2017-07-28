#ifndef THC_GENERIC_FILE
#define THC_GENERIC_FILE "generic/THCTensorMathReduce.h"
#else

#if defined(THC_REAL_IS_FLOAT) || defined(THC_REAL_IS_DOUBLE) || defined(THC_REAL_IS_HALF)

<<<<<<< HEAD
THC_API void THCTensor_(renorm)(THCState *state, THCTensor* self, THCTensor* src, real value, int dimension, real max_norm);
THC_API void THCTensor_(std)(THCState *state, THCTensor *self, THCTensor *src, int dim, int flag);
THC_API void THCTensor_(norm)(THCState *state, THCTensor* self, THCTensor* src, real value, int dimension);
THC_API void THCTensor_(var)(THCState *state, THCTensor *self, THCTensor *src, int dim, int flag);
=======
THC_API void THCTensor_(renorm)(THCState *state, THCTensor* self, THCTensor* src, real value, long dimension, real max_norm);
THC_API void THCTensor_(std)(THCState *state, THCTensor *self, THCTensor *src, long dim, int biased, int keepdim);
THC_API void THCTensor_(norm)(THCState *state, THCTensor* self, THCTensor* src, real value, long dimension, int keepdim);
THC_API void THCTensor_(var)(THCState *state, THCTensor *self, THCTensor *src, long dim, int biased, int keepdim);
>>>>>>> master

THC_API accreal THCTensor_(stdall)(THCState *state, THCTensor *self, int biased);
THC_API accreal THCTensor_(normall)(THCState *state, THCTensor *self, real value);
THC_API accreal THCTensor_(varall)(THCState *state, THCTensor *self, int biased);

#endif

<<<<<<< HEAD
THC_API void THCTensor_(sum)(THCState *state, THCTensor *self, THCTensor *src, int dim);
THC_API void THCTensor_(prod)(THCState *state, THCTensor *self, THCTensor *src, int dim);
THC_API void THCTensor_(mean)(THCState *state, THCTensor *self, THCTensor *src, int dim);
=======
THC_API void THCTensor_(sum)(THCState *state, THCTensor *self, THCTensor *src, long dim, int keepdim);
THC_API void THCTensor_(prod)(THCState *state, THCTensor *self, THCTensor *src, long dim, int keepdim);
THC_API void THCTensor_(mean)(THCState *state, THCTensor *self, THCTensor *src, long dim, int keepdim);
>>>>>>> master

THC_API accreal THCTensor_(sumall)(THCState *state, THCTensor *self);
THC_API accreal THCTensor_(prodall)(THCState *state, THCTensor *self);
THC_API accreal THCTensor_(meanall)(THCState *state, THCTensor *self);

THC_API void THCTensor_(min)(THCState *state,
                             THCTensor *values,
                             THCudaLongTensor *indices,
<<<<<<< HEAD
                             THCTensor *src, int dim);
THC_API void THCTensor_(max)(THCState *state,
                             THCTensor *values,
                             THCudaLongTensor *indices,
                             THCTensor *src, int dim);
=======
                             THCTensor *src, long dim, int keepdim);
THC_API void THCTensor_(max)(THCState *state,
                             THCTensor *values,
                             THCudaLongTensor *indices,
                             THCTensor *src, long dim, int keepdim);
>>>>>>> master

THC_API real THCTensor_(minall)(THCState *state, THCTensor *self);
THC_API real THCTensor_(maxall)(THCState *state, THCTensor *self);
THC_API real THCTensor_(medianall)(THCState *state, THCTensor *self);

THC_API void THCTensor_(median)(THCState *state,
				THCTensor *values,
				THCudaLongTensor *indices,
				THCTensor *src, long dim, int keepdim);

THC_API accreal THCTensor_(dist)(THCState *state, THCTensor *self, THCTensor *src,
                              real value);

#endif
