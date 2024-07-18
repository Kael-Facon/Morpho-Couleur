#include "app.hh"

using namespace std;

App::App(){
    env = Env();
}

void App::Windows()
{
    ImGui::Begin("Actions");
    Actions();
    ImGui::End();

    ImGui::Begin("Color Options");
    ColorOptions();
    ImGui::End();

    ImGui::Begin("Viewport");

    ImGuiIO &io = ImGui::GetIO();
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImGui::Image((void*)(intptr_t)env.render_image,
                 ImVec2(static_cast<float>(env.image->width), static_cast<float>(env.image->height)));

    if (ImGui::Button("Save Render"))
        ImGui::OpenPopup("save_render");
    if (ImGui::BeginPopup("save_render"))
    {
        static char filename[128] = "";
        ImGui::InputText("File Name", filename, IM_ARRAYSIZE(filename));
        ImGui::SameLine();
        if (ImGui::Button("Save file"))
            env.image->save_as_ppm("../test/" + string(filename) + ".ppm");
        ImGui::EndPopup();
    }

    ImGui::SameLine();
    if (ImGui::Button("Prev Image"))
    {
        index_image -= 1;
        env.change_image();
        env.render();
    }
    ImGui::SameLine();
    if (ImGui::Button("Next Image"))
    {
        index_image += 1;
        env.change_image();
        env.render();
    }
    ImGui::SameLine();
    if (ImGui::Button("Reinitialize"))
    {
        delete env.image;
        slides[index_image] = load_image(slides_path[index_image]);
        env.image = slides[index_image];
        env.render();
    }


    ImGui::SameLine();
    Inputs(io, pos);

    ImGui::End();

//    ImGui::ShowDemoWindow();
}

void App::Actions() {
    if (ImGui::RadioButton("Disk", &env.form, 0)) {
        env.shape = morpho_shape(env.size, static_cast<morpho_shape::type>(env.form));
        env.render();
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Square", &env.form, 1)) {
        env.shape = morpho_shape(env.size, static_cast<morpho_shape::type>(env.form));
        env.render();
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Diamond", &env.form, 2)) {
        env.shape = morpho_shape(env.size, static_cast<morpho_shape::type>(env.form));
        env.render();
    }
    if (ImGui::RadioButton("Morpho", &env.form, 3)) {
        env.shape = morpho_shape(env.size, static_cast<morpho_shape::type>(env.form));
        env.render();
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Bow Tie", &env.form, 4)) {
        env.shape = morpho_shape(env.size, static_cast<morpho_shape::type>(env.form));
        env.render();
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Rabbit", &env.form, 5)) {
        env.shape = morpho_shape(env.size, static_cast<morpho_shape::type>(env.form));
        env.render();
    }
//    ImGui::SameLine();
//    if (ImGui::RadioButton("No Grid", &env.form, 1)) { env.render(); }

    if (ImGui::Button("Update")) {
        env.shape = morpho_shape(env.size, static_cast<morpho_shape::type>(env.form));
        env.render();
    }
    ImGui::SameLine();
    ImGui::SliderInt("Size", &env.size, 1, 15);

    // Gray
    ImGui::Text("Gray");
    if (ImGui::Button("Dilation_bw")) { env.morpho(dilation_bw); }
    ImGui::SameLine();
    if (ImGui::Button("Erosion_bw")) { env.morpho(erosion_bw); }

    if (ImGui::Button("Opening_bw")) { env.morpho(open_morpho_bw); }
    ImGui::SameLine();
    if (ImGui::Button("Closing_bw")) { env.morpho(close_morpho_bw); }

    // RGB
    ImGui::Text("RGB");
    if (ImGui::Button("Dilation_rgb")) { env.morpho(dilation_rgb); }
    ImGui::SameLine();
    if (ImGui::Button("Erosion_rgb")) { env.morpho(erosion_rgb); }

    if (ImGui::Button("Opening_rgb")) { env.morpho(open_morpho_rgb); }
    ImGui::SameLine();
    if (ImGui::Button("Closing_rgb")) { env.morpho(close_morpho_rgb); }

    // HSV (Value)
    ImGui::Text("HSV (Value)");
    if (ImGui::Button("Dilation_hsv_v")) { env.morpho(dilation_hsv_v); }
    ImGui::SameLine();
    if (ImGui::Button("Erosion_hsv_v")) { env.morpho(erosion_hsv_v); }

    if (ImGui::Button("Opening_hsv_v")) { env.morpho(open_morpho_hsv_v); }
    ImGui::SameLine();
    if (ImGui::Button("Closing_hsv_v")) { env.morpho(close_morpho_hsv_v); }

    // HSV (Saturation)
    ImGui::Text("HSV (Saturation)");
    if (ImGui::Button("Dilation_hsv_s")) { env.morpho(dilation_hsv_s); }
    ImGui::SameLine();
    if (ImGui::Button("Erosion_hsv_s")) { env.morpho(erosion_hsv_s); }

    if (ImGui::Button("Opening_hsv_s")) { env.morpho(open_morpho_hsv_s); }
    ImGui::SameLine();
    if (ImGui::Button("Closing_hsv_s")) { env.morpho(close_morpho_hsv_s); }

    // HSV (Saturation and Value)
    ImGui::Text("HSV (Saturation and Value)");
    if (ImGui::Button("Dilation_hsv_sv")) { env.morpho(dilation_hsv_sv); }
    ImGui::SameLine();
    if (ImGui::Button("Erosion_hsv_sv")) { env.morpho(erosion_hsv_sv); }

    if (ImGui::Button("Opening_hsv_sv")) { env.morpho(open_morpho_hsv_sv); }
    ImGui::SameLine();
    if (ImGui::Button("Closing_hsv_sv")) { env.morpho(close_morpho_hsv_sv); }
}

void App::ColorOptions() {
    static bool alpha_preview = true;
    static bool alpha_half_preview = false;
    static bool drag_and_drop = true;
    static bool options_menu = true;
    static bool hdr = false;
    ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

    Color cc = Color(1.0,1.0,1.0);
    static ImVec4 color = ImVec4(cc.r, cc.g, cc.b, 255.0f / 255.0f);
    static bool side_preview = true;
    static int display_mode = 0;
    static int picker_mode = 0;
    ImGui::Checkbox("With Side Preview", &side_preview);

    ImGui::Combo("Display Mode", &display_mode, "Auto/Current\0None\0RGB Only\0HSV Only\0Hex Only\0");
    ImGuiColorEditFlags flags = misc_flags;
    if (!side_preview)     flags |= ImGuiColorEditFlags_NoSidePreview;
    if (picker_mode == 1)  flags |= ImGuiColorEditFlags_PickerHueBar;
    if (picker_mode == 2)  flags |= ImGuiColorEditFlags_PickerHueWheel;
    if (display_mode == 1) flags |= ImGuiColorEditFlags_NoInputs;
    if (display_mode == 2) flags |= ImGuiColorEditFlags_DisplayRGB;
    if (display_mode == 3) flags |= ImGuiColorEditFlags_DisplayHSV;
    if (display_mode == 4) flags |= ImGuiColorEditFlags_DisplayHex;
    ImGui::ColorPicker4("MyColor##4", (float*)&color, flags);

    // LAB
    ImGui::Text("LAB");
    if (ImGui::Button("Dilation_lab")) { env.morpho_lab(dilation_lab, color.x * 255, color.y * 255, color.z * 255); }
    ImGui::SameLine();
    if (ImGui::Button("Erosion_lab")) { env.morpho_lab(erosion_lab, color.x * 255, color.y * 255, color.z * 255); }

    if (ImGui::Button("Opening_lab")) { env.morpho_lab(open_morpho_lab, color.x * 255, color.y * 255, color.z * 255); }
    ImGui::SameLine();
    if (ImGui::Button("Closing_lab")) { env.morpho_lab(close_morpho_lab, color.x * 255, color.y * 255, color.z * 255); }
}

void App::PrintObjInfo() const {
    ImGui::Text("Nothing to Print");
}

void App::Inputs(const ImGuiIO& io, ImVec2 pos) {
    float region_sz = 32.0f;
    float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
    float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
    if (region_x < 0.0f) { return; }
    else if (region_x > 1600 - region_sz) { return; }
    if (region_y < 0.0f) { return; }
    else if (region_y > 900 - region_sz) { return; }
    ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
    ImGui::SameLine();
    ImGui::Text("Mouse down:");
    for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) {
        if (io.MouseDownDuration[i] > 0.01)
            return;
        if (ImGui::IsMouseDown(i)) {
            env.render();
        }
    }
    ImGui::SameLine();
    ImGui::Text("Keys down:");
    struct funcs {
        static bool IsLegacyNativeDupe(ImGuiKey key) {
            return key >= 0 && key < 512 && ImGui::GetIO().KeyMap[key] != -1;
        }
    };

    auto start_key = (ImGuiKey)0;
    for (ImGuiKey key = start_key; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
        if (funcs::IsLegacyNativeDupe(key) || !ImGui::IsKeyDown(key))
            continue;
        ImGui::SameLine(); ImGui::Text((key < ImGuiKey_NamedKey_BEGIN) ? "\"%s\"" : "\"%s\" %d", ImGui::GetKeyName(key), key);
//        if (key == 513) { // Left Arrow
//            index_image -= 1;
//            env.change_image();
//            env.render();
//        }
//        if (key == 514) { // Right Arrow
//            index_image += 1;
//            env.change_image();
//            env.render();
//        }
    }
}