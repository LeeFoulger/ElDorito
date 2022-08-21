#include "TlsData.hpp"

#include <Windows.h>
#include <cseries/cseries.hpp>

namespace Blam::Memory
{
	// modified https://github.com/citizenfx/fivem/blob/f3bb0460562b1eb1a7f9652ffcf73ad7282fd45e/code/client/shared/Hooking.h#L91-L113
	s_thread_local_storage* GetTls()
	{
		static dword tls_index = 'NOGO';
		if (tls_index == 'NOGO')
		{
			byte* module_base = reinterpret_cast<byte*>(GetModuleHandle(NULL));
			PIMAGE_DOS_HEADER dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_base);
			PIMAGE_NT_HEADERS nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(module_base + dos_header->e_lfanew);
			PIMAGE_TLS_DIRECTORY tls_directory = reinterpret_cast<PIMAGE_TLS_DIRECTORY>(module_base + nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
			tls_index = *reinterpret_cast<dword*>(tls_directory->AddressOfIndex);
		}

		if (tls_index == 'NOGO')
			return nullptr;

		void** tls_ptr = reinterpret_cast<void**>(__readfsdword(0x2C));
		return reinterpret_cast<s_thread_local_storage*>(tls_ptr[tls_index]);
	}
}
