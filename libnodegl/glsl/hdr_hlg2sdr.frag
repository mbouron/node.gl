#include hdr.glsl

/* HLG Reference EOTF (linearize: R'G'B' HDR → RGB HDR), normalized, ITU-R BT.2100 */
vec3 hlg_eotf(vec3 x)
{
    const float a = 0.17883277;
    const float b = 0.28466892;
    const float c = 0.55991073;
    return mix(x * x / 3.0, (exp((x - c) / a) + b) / 12.0, lessThan(vec3(0.5), x));
}

/* HLG Reference OOTF (linear scene light → linear display light), ITU-R BT.2100 */
vec3 hlg_ootf(vec3 x)
{
    return x * vec3(pow(dot(luma_coeff, x), 0.2));
}

void main()
{
    vec4 hdr = ngl_texvideo(tex, var_tex_coord);
    vec3 sdr = bt2020_to_bt709(tonemap(hlg_ootf(hlg_eotf(hdr.rgb))));
    ngl_out_color = vec4(sdr, hdr.a);
}
