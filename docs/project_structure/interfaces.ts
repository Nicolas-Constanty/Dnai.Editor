interface Common {
  uid: string;
  name: string;
  description: string;
}

interface Position {
  x: number;
  y: number;
}

interface Identity {
  linked_uid: string;
}

interface Class extends Common, Position {
  attributes: Variable[];
  methods: Function[];
  functions: Function[];
  classes: Class[];
}

interface Context extends Common, Position {
  variables: Variable[];
  contexts: Context[];
  functions: Function[];
  classes: Class[];
}

interface Flow extends Common, Identity {

}

interface Function extends Common, Position {
  variables: Variable[];
  inputs: Input[];
  outputs: Output[];
  nodes: Node[];
}

interface Input extends Variable, Identity {

}

interface Output extends Variable, Identity {

}

interface Node extends Common {
  function: string;
  inputs: Input[];
  outputs: Output[];
  flows_in: Flow[];
  flows_out: Flow[];
}

interface Variable extends Common, Position {
  value: any;
  type: string;
  internal: boolean;
}
