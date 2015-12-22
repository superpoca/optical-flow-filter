/**
 * \file imagemodel.h
 * \brief type declarations vision pipelines.
 * \copyright 2015, Juan David Adarve, ANU. See AUTHORS for more details
 * \license 3-clause BSD, see LICENSE for more details
 */

#ifndef FLOWFILTER_GPU_IMAGEMODEL_H_
#define FLOWFILTER_GPU_IMAGEMODEL_H_

#include <cuda.h>
#include <cuda_runtime.h>

#include "flowfilter/gpu/pipeline.h"
#include "flowfilter/gpu/image.h"

namespace flowfilter {
    namespace gpu {

        
        class ImageModel : public Stage {

        public:
            ImageModel();

            /**
             * \brief creates an image model stage with a given input image
             *
             * This constructor internally calles configure() so that the
             * stage is ready to perform computations.
             */
            ImageModel(flowfilter::gpu::GPUImage inputImage);

            ~ImageModel();

        public:

            /**
             * \brief configures the stage.
             *
             * After configuration, calls to compute()
             * are valid.
             * Input buffers should not change after
             * this method has been called.
             */
            void configure();

            /**
             * \brief performs computation of brightness parameters
             */
            void compute();

            //#########################
            // Pipeline stage inputs
            //#########################
            void setInputImage(flowfilter::gpu::GPUImage img);

            //#########################
            // Pipeline stage outputs
            //#########################
            flowfilter::gpu::GPUImage getImageConstantDevice();
            flowfilter::gpu::GPUImage getImageGradientDevice();

        private:

            // tell if the stage has been configured
            bool __configured;

            // inputs
            flowfilter::gpu::GPUImage __inputImage;
            flowfilter::gpu::GPUTexture __inputImageTexture;

            // outputs
            flowfilter::gpu::GPUImage __imageConstant;
            flowfilter::gpu::GPUImage __imageGradient;

            // intermediate buffers

            /** 2-channels image with X and Y filtering version of inputImage */
            flowfilter::gpu::GPUImage __imageFiltered;
            flowfilter::gpu::GPUTexture __imageFilteredTexture;
        };

    }; // namespace gpu
}; // namespace flowfilter

#endif // FLOWFILTER_GPU_IMAGEMODEL_H_