#include <iostream>

#include <AVL_Lite.h>
#include<../headers/main.h>

#include "UserFilter.h"
#include "UserFilterLibrary.hxx"

namespace avs
{
	// Example image processing filter
	class CustomThreshold : public UserFilter
	{
	private:
		// Non-trivial outputs must be defined as a filed to retain data after filter execution. 
		avl::Image outImage;

	public:
		// Defines the inputs, the outputs and the filter metadata
		void Define() override
		{
			SetName		(L"CustomThreshold");
			SetCategory	(L"Image::Image Thresholding");
			SetImage	(L"CustomThreshold_16.png");	
			SetImageBig	(L"CustomThreshold_48.png");
			SetTip		(L"Binarizes 8-bit images");

			//					 Name						Type				Default		Tool-tip
			AddInput			(L"inImage",				L"Image",			L"",		L"Input image"    );
			AddInput			(L"inThreshold",			L"Integer<0, 255>",	L"128",		L"Threshold value");
			AddOutput			(L"outImage",				L"Image",						L"Output image"   );
		}

		// Computes output from input data
		int Invoke() override
		{
			// Get data from the inputs
			avl::Image inImage;
			int inThreshold;
			
			ReadInput(L"inImage", inImage);
			ReadInput(L"inThreshold", inThreshold);

			if (inImage.Type() != avl::PlainType::UInt8)
				throw atl::DomainError("Only uint8 pixel type are supported.");

			// Get image properties
			int height = inImage.Height();

			// Prepare output image in this same format as input
			outImage.Reset(inImage, atl::NIL);

			// Enumerate each row
			for (int y = 0; y < height; ++y)
			{
				// Get row pointers
				const atl::uint8* p = inImage.RowBegin<atl::uint8>(y);
				const atl::uint8* e = inImage.RowEnd<atl::uint8>(y);
				atl::uint8*       q = outImage.RowBegin<atl::uint8>(y);

				// Loop over the pixel components
				while (p < e)
				{
					(*q++) = (*p++) < inThreshold ? 0 : 255;
				}
			}

			// Set output data
			WriteOutput(L"outImage", outImage);

			// Continue program
			return INVOKE_NORMAL;
		}
	};
	
	// Builds the filter factory
	class RegisterUserObjects
	{
	public:
		RegisterUserObjects()
		{
			// Remember to register every filter exported by the user filter library
			RegisterFilter(CreateInstance<CustomThreshold>);
		}
	};

	static RegisterUserObjects registerUserObjects;
}
