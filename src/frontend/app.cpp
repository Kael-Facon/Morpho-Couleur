#include "app.hh"

using namespace std;

App::App(){
    env = Env();
    create_disk(); create_square(); create_diamond();
}

App::App(const char* filename) {
    env = Env(filename);
    create_disk(); create_square(); create_diamond();
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
    Inputs(io, pos);

    ImGui::End();

//    ImGui::ShowDemoWindow();
}

void App::Actions() {
    if (ImGui::RadioButton("Disk", &env.form, 0)) { env.render(); }
    ImGui::SameLine();
    if (ImGui::RadioButton("Square", &env.form, 1)) { env.render(); }
    ImGui::SameLine();
    if (ImGui::RadioButton("Diamond", &env.form, 2)) { env.render(); }
//    ImGui::SameLine();
//    if (ImGui::RadioButton("No Grid", &env.form, 1)) { env.render(); }
    if (ImGui::Button("B&W Morph")) {

    }
    if (ImGui::Button("Morph RGB")) {
        //Lab test_col = rbg_to_lab(0, 255, 0);
        uint8_t* res = dilation_hsv_v(*env.image, morpho_disk);
        // uint8_t* test_gray = app.env.image->get_gray();
        // uint8_t* res = erosion_col1(app.env.image->get_char_data_copy(), test_gray, app.env.image->width, app.env.image->height, morpho_disk);
        env.image->update_char_data(res);

        // res = dilation_col1(app.env.image->get_char_data_copy(), app.env.image->get_gray(), app.env.image->width, app.env.image->height, morpho_disk);
        // app.env.image->update_char_data(res);
    }
    if (ImGui::Button("Morph HSV Value")) {
        uint8_t* res;
        if (env.form == 0)
            res = dilation_hsv_v(*env.image, morpho_disk);
        if (env.form == 0)
            res = dilation_hsv_v(*env.image, morpho_square);
        if (env.form == 0)
            res = dilation_hsv_v(*env.image, morpho_diamond);

        env.image->update_char_data(res);
        env.render();
    }
    if (ImGui::Button("Morph HSV Saturation")) {
//        env.image->update_char_data(res);
    }
    if (ImGui::Button("Morph HSV Mix")) {
//        env.image->update_char_data(res);
    }
    if (ImGui::Button("Morph LAB")) {
//        env.image->update_char_data(res);
    }
    if (ImGui::Button("Morph HSV Mix")) {
//        env.image->update_char_data(res);
    }
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

    if (ImGui::Button("Update Color")) {
        // Update Color
    }
}

void App::PrintObjInfo() const {
    ImGui::Text("Nothing to Print");
}

void App::Inputs(const ImGuiIO& io, ImVec2 pos) {
    float region_sz = 32.0f;
    float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
    float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
    if (region_x < 0.0f) { return; }
    else if (region_x > 1280 - region_sz) { return; }
    if (region_y < 0.0f) { return; }
    else if (region_y > 720 - region_sz) { return; }
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
//            env.scene.move_camera_y(-15);
//            env.render();
//        }
    }
}