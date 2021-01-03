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

        // Graphics
        static bool graphicsTreeOpen = true;
        ImGui::SetNextItemOpen(graphicsTreeOpen);
        if (graphicsTreeOpen = ImGui::TreeNode("Graphics"))
        {
            static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
            ImGui::SetNextItemWidth(120);
            ImGui::ColorEdit3("Clear Color", (float*)&clear_color); // Edit 3 floats representing a color
            GfxControllables::SetClearColor(Vector4f(clear_color.x, clear_color.y, clear_color.z, clear_color.w));

            static ImVec4 prim_color = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
            ImGui::SetNextItemWidth(120);
            ImGui::ColorEdit3("Primitive Color", (float*)&prim_color); // Edit 3 floats representing a color
            GfxControllables::SetPrimitiveColor(Vector4f(prim_color.x, prim_color.y, prim_color.z, prim_color.w));

            static int32 currentPipelineStateIdx = 0;
            const char* pipelineStates[] = { "Default", "Wireframe", "FronFaceCull" };
            ImGui::SetNextItemWidth(120);
            ImGui::Combo("Render Mode", &currentPipelineStateIdx, pipelineStates, ToUnderlyingType(PipelineState)(PipelineState::_Count));
            GfxControllables::SetPipelineState(static_cast<PipelineState>(currentPipelineStateIdx));

            ImGui::TreePop();
        }

        ImGui::NewLine();

        // Camera
        if (ImGui::TreeNode("Camera"))
        {
            static float32 fov = GfxControllables::GetFOV();
            ImGui::SetNextItemWidth(80);
            ImGui::DragFloat("FOV", &fov, 0.5f, 0.0f, 120.0f, "%.2f", ImGuiSliderFlags_None);
            GfxControllables::SetFOV(fov);

            static float32 translationMult = GfxControllables::GetCamTranslationSpeedMult();
            ImGui::SetNextItemWidth(80);
            ImGui::DragFloat("Translation Speed Multiplier", &translationMult, 0.005f, 0.0f, 20.0f, "%.4f", ImGuiSliderFlags_None);
            GfxControllables::SetCamTranslationSpeedMult(translationMult);

            static float32 rotationMult = GfxControllables::GetCamRotationSpeedMult();
            ImGui::SetNextItemWidth(80);
            ImGui::DragFloat("Rotation Speed Multiplier", &rotationMult, 0.005f, 0.0f, 20.0f, "%.4f", ImGuiSliderFlags_None);
            GfxControllables::SetCamRotationSpeedMult(rotationMult);

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