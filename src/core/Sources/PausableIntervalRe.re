open UtilsRe;

open TypeRe;

let pausableInterval = (period, action, sink) =>
  switch action {
  | Start =>
    let i = ref(0);
    let interval = ref(None);
    let pause = () =>
      switch interval^ {
      | None => ()
      | Some(id) =>
        Js.Global.clearInterval(id);
        interval := None;
      };
    let resume = () =>
      interval :=
        Some(
          Js.Global.setInterval(
            () => {
              whenTalk(sink, talk => talk(Data, Content(i^)));
              i := i^ + 1;
            },
            period
          )
        );
    whenTalk(sink, talk =>
      talk(
        Start,
        Talkback(
          (action, _) =>
            switch action {
            | End => pause()
            | Start => resume()
            | Data =>
              switch interval^ {
              | Some(_p) => pause()
              | None => resume()
              }
            }
        )
      )
    );
    resume();
  | _ => ()
  };