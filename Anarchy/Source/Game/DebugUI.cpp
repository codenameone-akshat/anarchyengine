#include "acpch.h"
#include "DebugUI.h"

#include <Graphics/ImGui/imgui.h>
#if defined(AC_D3D12) && defined(PLATFORM_WINDOWS)
#include <Graphics/D3D12/D3D12GraphicsPSOManager.h>
#endif // AC_D3D12 && PLATFORM_WINDOWS
#include <Graphics/GfxControllables.h>

namespace anarchy::sandbox
{
    void DebugUI::Draw()
    {
        //---------------------------------------------------------------------------------------------------------------------------------

        // Debug Menu
        ImGui::Begin("Debug Menu");

        static bool graphicsTreeOpen = true;
        ImGui::SetNextItemOpen(graphicsTreeOpen);
        if (graphicsTreeOpen = ImGui::TreeNode("Graphics"))
        {
            static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
            ImGui::ColorEdit3("Clear Color", (float*)&clear_color); // Edit 3 floats representing a color
            GfxControllables::SetClearColor(Vector4f(clear_color.x, clear_color.y, clear_color.z, clear_color.w));

            ImGui::NewLine();

            static ImVec4 prim_color = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
            ImGui::ColorEdit3("Primitive Color", (float*)&prim_color); // Edit 3 floats representing a color
            GfxControllables::SetPrimitiveColor(Vector4f(prim_color.x, prim_color.y, prim_color.z, prim_color.w));

            ImGui::NewLine();

            static int32 currentPipelineStateIdx = 0;
            const char* pipelineStates[] = { "Default", "Wireframe", "FronFaceCull" };
            ImGui::Combo("Render Mode", &currentPipelineStateIdx, pipelineStates, ToUnderlyingType(PipelineState)(PipelineState::_Count));
            GfxControllables::SetPipelineState(static_cast<PipelineState>(currentPipelineStateIdx));

            ImGui::TreePop();
        }
        ImGui::End();

        //---------------------------------------------------------------------------------------------------------------------------------

        // Frame Stats
        ImGui::Begin("Stats", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
        ImGui::Text("%.3f ms", 1000.0f / ImGui::GetIO().Framerate);
        ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
        ImGui::End();
    }
}