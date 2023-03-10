from pynodegl_utils.misc import SceneCfg, scene

import pynodegl as ngl


@scene(fast=scene.Bool(), segment_time=scene.Range(range=[0.1, 10], unit_base=10), constrained_timeranges=scene.Bool())
def parallel_playback(cfg: SceneCfg, fast=True, segment_time=2.0, constrained_timeranges=False):
    """
    Parallel media playback, flipping between the two sources.

    The fast version makes sure the textures continue to be updated even though
    they are not displayed. On the other hand, the slow version will update the
    textures only when needed to be displayed, causing potential seek in the
    underlying media, and thus undesired delays.
    """
    m1 = ngl.Media(cfg.medias[0].filename, label="media #1")
    m2 = ngl.Media(cfg.medias[0].filename, label="media #2")

    t1 = ngl.Texture2D(data_src=m1, label="texture #1")
    t2 = ngl.Texture2D(data_src=m2, label="texture #2")

    render1 = ngl.RenderTexture(t1)
    render2 = ngl.RenderTexture(t2)

    text_settings = {
        "box_corner": (-1, 1 - 0.2, 0),
        "box_height": (0, 0.2, 0),
        "aspect_ratio": cfg.aspect_ratio,
    }
    render1 = ngl.Group(children=(render1, ngl.Text("media #1", **text_settings)))
    render2 = ngl.Group(children=(render2, ngl.Text("media #2", **text_settings)))

    rf1 = ngl.TimeRangeFilter(render1)
    rf2 = ngl.TimeRangeFilter(render2)

    if constrained_timeranges:
        rf1.set_prefetch_time(segment_time / 3.0)
        rf2.set_prefetch_time(segment_time / 3.0)
        rf1.set_max_idle_time(segment_time / 2.0)
        rf2.set_max_idle_time(segment_time / 2.0)

    t = 0
    rr1 = []
    rr2 = []
    while t < cfg.duration:
        rr1.append(ngl.TimeRangeModeCont(t))
        rr1.append(ngl.TimeRangeModeNoop(t + segment_time))

        rr2.append(ngl.TimeRangeModeNoop(t))
        rr2.append(ngl.TimeRangeModeCont(t + segment_time))

        t += 2 * segment_time

    rf1.add_ranges(*rr1)
    rf2.add_ranges(*rr2)

    g = ngl.Group()
    g.add_children(rf1, rf2)
    if fast:
        g.add_children(t1, t2)
    return g


@scene(transition_start=scene.Range(range=[0, 30]), transition_duration=scene.Range(range=[0, 30]))
def simple_transition(cfg: SceneCfg, transition_start=2, transition_duration=4):
    """Fading transition between two medias"""

    cfg.duration = transition_start * 2 + transition_duration

    vertex = cfg.get_vert("dual-tex")
    fragment = cfg.get_frag("tex-mix")

    q = ngl.Quad((-1, -1, 0), (2, 0, 0), (0, 2, 0))
    p1_2 = ngl.Program(vertex=vertex, fragment=fragment)
    p1_2.update_vert_out_vars(var_tex0_coord=ngl.IOVec2(), var_tex1_coord=ngl.IOVec2())

    m1 = ngl.Media(cfg.medias[0].filename, label="media #1")
    m2 = ngl.Media(cfg.medias[1 % len(cfg.medias)].filename, label="media #2")

    animkf_m2 = [
        ngl.AnimKeyFrameFloat(transition_start, 0),
        ngl.AnimKeyFrameFloat(transition_start + cfg.duration, cfg.duration),
    ]
    m2.set_time_anim(ngl.AnimatedTime(animkf_m2))

    t1 = ngl.Texture2D(data_src=m1, label="texture #1")
    t2 = ngl.Texture2D(data_src=m2, label="texture #2")

    render1 = ngl.RenderTexture(t1, label="render #1")
    render2 = ngl.RenderTexture(t2, label="render #2")

    delta_animkf = [
        ngl.AnimKeyFrameFloat(transition_start, 1.0),
        ngl.AnimKeyFrameFloat(transition_start + transition_duration, 0.0),
    ]
    delta = ngl.AnimatedFloat(delta_animkf)

    render1_2 = ngl.Render(q, p1_2, label="transition")
    render1_2.update_frag_resources(tex0=t1, tex1=t2)
    render1_2.update_frag_resources(delta=delta)

    rr1 = []
    rr2 = []
    rr1_2 = []

    rr1.append(ngl.TimeRangeModeNoop(transition_start))

    rr2.append(ngl.TimeRangeModeNoop(0))
    rr2.append(ngl.TimeRangeModeCont(transition_start + transition_duration))

    rr1_2.append(ngl.TimeRangeModeNoop(0))
    rr1_2.append(ngl.TimeRangeModeCont(transition_start))
    rr1_2.append(ngl.TimeRangeModeNoop(transition_start + transition_duration))

    rf1 = ngl.TimeRangeFilter(render1, ranges=rr1)
    rf2 = ngl.TimeRangeFilter(render2, ranges=rr2)
    rf1_2 = ngl.TimeRangeFilter(render1_2, ranges=rr1_2)

    g = ngl.Group()
    g.add_children(rf1, rf1_2, rf2)

    return g
