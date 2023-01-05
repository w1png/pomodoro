struct config {
  int pomodoro;
  int short_break;
  int long_break;
};
struct config read_config();
void write_config(struct config);

