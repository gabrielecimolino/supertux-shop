#include <config.h>

#include "flame.h"

Flame::Flame(const lisp::Lisp& reader)
  : angle(0), radius(100), speed(2)
{
  reader.get("x", start_position.x);
  reader.get("y", start_position.y);
  reader.get("radius", radius);
  reader.get("speed", speed);
  bbox.set_pos(Vector(start_position.x + cos(angle) * radius,
                      start_position.y + sin(angle) * radius));
  bbox.set_size(32, 32);  
  sprite = sprite_manager->create("flame");
}

void
Flame::write(lisp::Writer& writer)
{
  writer.start_list("flame");

  writer.write_float("x", start_position.x);
  writer.write_float("y", start_position.y);
  writer.write_float("radius", radius);
  writer.write_float("speed", speed);

  writer.end_list("flame");
}

void
Flame::active_action(float elapsed_time)
{
  angle = fmodf(angle + elapsed_time * speed, 2*M_PI);
  Vector newpos(start_position.x + cos(angle) * radius,
                start_position.y + sin(angle) * radius);
  movement = newpos - get_pos();
}

void
Flame::kill_fall()
{
}

IMPLEMENT_FACTORY(Flame, "flame")

