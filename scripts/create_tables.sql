CREATE TABLE public.profiles (
    id int4 GENERATED ALWAYS AS IDENTITY( INCREMENT BY 1 MINVALUE 1 MAXVALUE 2147483647 START 1 CACHE 1 NO CYCLE) NOT NULL,
    "name" text NOT NULL,
    CONSTRAINT profiles_pk PRIMARY KEY (id)
);

CREATE TABLE public.tasks (
    "name" text NOT NULL,
    score float4 NOT NULL,
    streak_name text NULL,
    id int4 GENERATED ALWAYS AS IDENTITY( INCREMENT BY 1 MINVALUE 1 MAXVALUE 2147483647 START 1 CACHE 1 NO CYCLE) NOT NULL,
  CONSTRAINT tasks_pk PRIMARY KEY (id)
);

CREATE TABLE public.done_tasks (
    id int4 GENERATED ALWAYS AS IDENTITY( INCREMENT BY 1 MINVALUE 1 MAXVALUE 2147483647 START 1 CACHE 1 NO CYCLE) NOT NULL,
    "date" date NOT NULL,
    profile_id int4 NOT NULL,
    task_id int4 NOT NULL,
    CONSTRAINT done_tasks_pk PRIMARY KEY (id)
);

ALTER TABLE public.done_tasks ADD CONSTRAINT done_tasks_profiles_fk FOREIGN KEY (profile_id) REFERENCES public.profiles(id);
ALTER TABLE public.done_tasks ADD CONSTRAINT done_tasks_tasks_fk FOREIGN KEY (task_id) REFERENCES public.tasks(id);
